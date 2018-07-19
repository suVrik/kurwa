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

namespace kw {
// Forward-declaration for Function-like syntax
template <typename Signature>
class Signal;

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
class Signal<Result(Arguments...)> {
public:
    /**
     * Construct a signal.
     */
    Signal() = default;

    Signal(const Signal&) = delete;
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
    uint32 connect(Object* object, Result (Object::*const callback)(Arguments...));

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
    uint32 connect(const Object* object, Result (Object::*const callback)(Arguments...) const);

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
    uint32 connect(const Object* object, const Callback callback);

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
    uint32 connect(const Callback callback);

    /**
     * Disconnect all the callbacks tied with the given 'object'.
     */
    void disconnect(const void* object);

    /**
     * Disconnect a callback with the given 'token'.
     */
    void disconnect(uint32 token);

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
        const void*                    object;
        uint32                         token;
    };

    List<CallbackData> callbacks;
};
} // namespace kw

#include <kw/base/internal/signal_impl.h>
