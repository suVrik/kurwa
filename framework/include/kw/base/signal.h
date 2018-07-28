/**
 *  Copyright (c) 2018, 21DOGZ.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *  except in compliance with the License. You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is
 *  distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#pragma once

#include <kw/base/function.h>
#include <kw/base/list.h>
#include <kw/base/types.h>
#include <kw/debug/assert.h>

#include <EASTL/type_traits.h>

namespace kw {
/**
 * Template-free base class for Signal.
 * Used in SignalListener.
 */
class ISignal {
public:
    /**
     * Disconnect all the callbacks tied with the given 'object'.
     */
    virtual void disconnect(const void* object) noexcept = 0;

protected:
    ISignal() = default;
};

// Forward-declaration for Function-like syntax
template <typename Signature>
class Signal;

/**
 * Signal listener is an inheritance-only class for other classes that connect to some signals and don't want to hustle
 * with disconnect (which would require saving a signal reference somewhere and writing some code in destructor).
 * What it does it basically remembers all the connections and disconnects in destructor.
 */
class SignalListener {
public:
    ~SignalListener() noexcept;

protected:
    SignalListener() = default;

private:
    List<ISignal*> m_signals;

    template <typename Signature>
    friend class Signal;
};

/**
 * Signal is a list of functions (called callbacks) with the same signature:
 * they don't return anything and their parameters are 'Arguments'.
 *
 * You can add functions to this list, you can remove them and you can call
 * all of them in the same order you added them (this is called emitting).
 *
 * So overall this is a convenient way of listening to and emitting events.
 */
template <typename Result, typename... Arguments>
class Signal<Result(Arguments...)> final : public ISignal {
public:
    /**
     * Construct a signal.
     */
    Signal()              = default;
    Signal(const Signal&) = delete;
    ~Signal() noexcept;
    Signal& operator=(const Signal&) = delete;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * struct MyStruct {
     *     void update();
     * };
     * MyStruct my_struct;
     * update.connect(&my_struct, &MyStruct::update);
     * \endcode
     */
    template <typename Object>
    uint32 connect(Object* object, Result (Object::*const callback)(Arguments...)) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * struct MyStruct {
     *     void update() noexcept;
     * };
     * MyStruct my_struct;
     * update.connect(&my_struct, &MyStruct::update);
     * \endcode
     */
    template <typename Object>
    uint32 connect(Object* object, Result (Object::*const callback)(Arguments...) noexcept) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * struct MyStruct {
     *     void update() const;
     * };
     * const MyStruct my_struct;
     * update.connect(&my_struct, &MyStruct::update);
     * \endcode
     */
    template <typename Object>
    uint32 connect(const Object* object, Result (Object::*const callback)(Arguments...) const) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * struct MyStruct {
     *     void update() const noexcept;
     * };
     * const MyStruct my_struct;
     * update.connect(&my_struct, &MyStruct::update);
     * \endcode
     */
    template <typename Object>
    uint32 connect(const Object* object, Result (Object::*const callback)(Arguments...) const noexcept) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * update.connect(this, [] {
     *     printf("Update is called!");
     * });
     * update.emit(); // Update is called!
     * \endcode
     */
    template <typename Object, typename Callback>
    eastl::enable_if_t<!eastl::is_member_function_pointer<Callback>::value, uint32> connect(Object* object, const Callback callback) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     * The 'object', just like a token, can be used to disconnect the callback.
     *
     * \code
     * update.connect(this, [] {
     *     printf("Update is called!");
     * });
     * update.emit(); // Update is called!
     * \endcode
     */
    template <typename Object, typename Callback>
    eastl::enable_if_t<!eastl::is_member_function_pointer<Callback>::value, uint32> connect(const Object* object, const Callback callback) noexcept;

    /**
     * Connect a callback to the signal and return an unique token, which can be used to disconnect a callback.
     *
     * \code
     * update.connect([] {
     *     printf("Callback is called!");
     * });
     * update.emit(); // Callback is called!
     * \endcode
     */
    template <typename Callback>
    uint32 connect(const Callback callback) noexcept;

    /**
     * Disconnect all the callbacks tied with the given 'object'.
     */
    void disconnect(const void* object) noexcept override;

    /**
     * Disconnect a callback with the given 'token'.
     */
    void disconnect(uint32 token) noexcept;

    /**
     * Call all the connected callbacks with the given 'arguments' in order from the first to the last
     * connected callback. The result of each callback, if any exists, is ignored.
     */
    void emit(Arguments... arguments);

    /**
     * Call all the connected callbacks with the given 'arguments' in order from the first to the last
     * connected callback. Return the result of applying the given 'adder' to every sequential pair of callbacks.
     *
     * The required adder signature: Result(Result, Result) — with optional const-reference qualifiers.
     *
     * \code
     * Signal<int()> signal;
     * signal.connect([]() -> int) {
     *     return 5;
     * });
     * signal.connect([]() -> int) {
     *     return 10;
     * });
     * int c = signal.emit([](int a, int b) {
     *     return a + b;
     * });
     * printf("%d", c); // 15
     * \endcode
     */
    template <typename Adder>
    Result emit(Arguments... arguments, const Adder adder);

private:
    struct CallbackData {
        Function<Result(Arguments...)> callback;
        const void* object;
        uint32 token;
        bool is_signal_listener;
    };

    template <typename Object>
    eastl::enable_if_t<eastl::is_base_of<SignalListener, Object>::value, void> handle_signal_listener(CallbackData& callback_data, Object* object) noexcept;

    template <typename Object>
    eastl::enable_if_t<!eastl::is_base_of<SignalListener, Object>::value, void> handle_signal_listener(CallbackData& callback_data, Object* object) noexcept;

    List<CallbackData> m_callbacks;
};
} // namespace kw

#include <kw/base/internal/signal_impl.h>
