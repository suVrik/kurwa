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

#include <kw/base/signal.h>

namespace kw {
namespace signal_details {
uint32 generate_unique_token();

template <typename Object, typename Callback, typename Result, typename... Arguments>
Function<Result(Arguments...)> method(Object object, Callback callback) {
    if constexpr (eastl::is_same_v<Result, void>) {
        return [ object, callback ](Arguments && ... arguments) noexcept(noexcept((object->*callback)(eastl::forward<Arguments>(arguments)...)))->void {
            (object->*callback)(eastl::forward<Arguments>(arguments)...);
        };
    } else {
        return [ object, callback ](Arguments && ... arguments) noexcept(noexcept((object->*callback)(eastl::forward<Arguments>(arguments)...)))->Result {
            return (object->*callback)(eastl::forward<Arguments>(arguments)...);
        };
    }
}
} // namespace signal_details

template <typename Result, typename... Arguments>
Signal<Result(Arguments...)>::~Signal() noexcept {
    for (auto& callback : m_callbacks) {
        if (callback.is_signal_listener) {
            auto listener = const_cast<SignalListener*>(reinterpret_cast<const SignalListener*>(callback.object));
            for (auto it = listener->m_signals.begin(); it != listener->m_signals.end();) {
                if (*it == this) {
                    it = listener->m_signals.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(Object* object, Result (Object::*const callback)(Arguments...)) noexcept {
    CallbackData data;
    data.callback = signal_details::method<Object*, Result (Object::*const)(Arguments...), Result, Arguments...>(object, callback);
    data.token = signal_details::generate_unique_token();
    handle_signal_listener(data, object);
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(Object* object, Result (Object::*const callback)(Arguments...) noexcept) noexcept {
    CallbackData data;
    data.callback = signal_details::method<Object*, Result (Object::*const)(Arguments...) noexcept, Result, Arguments...>(object, callback);
    data.token = signal_details::generate_unique_token();
    handle_signal_listener(data, object);
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(const Object* object, Result (Object::*const callback)(Arguments...) const) noexcept {
    static_assert(!eastl::is_base_of<SignalListener, Object>::value, "You're trying to connect a callback tied with a "
                                                                     "const instance of SignalListener, "
                                                                     "which is not allowed! To connect a "
                                                                     "SignalListener to a signal, it's required "
                                                                     "to change the SignalListener.");
    CallbackData data;
    data.callback = signal_details::method<const Object*, Result (Object::*const)(Arguments...) const, Result, Arguments...>(object, callback);
    data.object = object;
    data.token = signal_details::generate_unique_token();
    data.is_signal_listener = false;
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(const Object* object, Result (Object::*const callback)(Arguments...) const noexcept) noexcept {
    static_assert(!eastl::is_base_of<SignalListener, Object>::value, "You're trying to connect a callback tied with a "
                                                                     "const instance of SignalListener, "
                                                                     "which is not allowed! To connect a "
                                                                     "SignalListener to a signal, it's required "
                                                                     "to change the SignalListener.");
    CallbackData data;
    data.callback = signal_details::method<const Object*, Result (Object::*const)(Arguments...) const noexcept, Result, Arguments...>(object, callback);
    data.object = object;
    data.token = signal_details::generate_unique_token();
    data.is_signal_listener = false;
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object, typename Callback>
eastl::enable_if_t<!eastl::is_member_function_pointer<Callback>::value, uint32> Signal<Result(Arguments...)>::connect(Object* object, const Callback callback) noexcept {
    CallbackData data;
    data.callback = Function<Result(Arguments...)>(callback);
    data.token = signal_details::generate_unique_token();
    handle_signal_listener(data, object);
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object, typename Callback>
eastl::enable_if_t<!eastl::is_member_function_pointer<Callback>::value, uint32> Signal<Result(Arguments...)>::connect(const Object* object, const Callback callback) noexcept {
    static_assert(!eastl::is_base_of<SignalListener, Object>::value, "You're trying to connect a callback tied with a "
                                                                     "const instance of SignalListener, "
                                                                     "which is not allowed! To connect a "
                                                                     "SignalListener to a signal, it's required "
                                                                     "to change the SignalListener.");

    CallbackData data;
    data.callback = Function<Result(Arguments...)>(callback);
    data.object = object;
    data.token = signal_details::generate_unique_token();
    data.is_signal_listener = false;
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Callback>
uint32 Signal<Result(Arguments...)>::connect(const Callback callback) noexcept {
    CallbackData data;
    data.callback = Function<Result(Arguments...)>(callback);
    data.object = nullptr;
    data.token = signal_details::generate_unique_token();
    data.is_signal_listener = false;
    m_callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::disconnect(const void* object) noexcept {
    for (auto it = m_callbacks.begin(); it != m_callbacks.end();) {
        if (it->object == object) {
            it = m_callbacks.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::disconnect(uint32 token) noexcept {
    for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        if (it->token == token) {
            m_callbacks.erase(it);
            break;
        }
    }
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::emit(Arguments... arguments) {
    for (auto& callback : m_callbacks) {
        callback.callback(arguments...);
    }
}

template <typename Result, typename... Arguments>
template <typename Adder>
Result Signal<Result(Arguments...)>::emit(Arguments... arguments, const Adder adder, eastl::conditional_t<eastl::is_same_v<Result, void>, int32, Result> default_value) {
    static_assert(!eastl::is_same_v<Result, void>, "This 'emit' signature is intended for non-void signals!");

    if (!m_callbacks.empty()) {
        Result result = m_callbacks.front().callback(arguments...);
        for (auto it = ++m_callbacks.begin(); it != m_callbacks.end(); ++it) {
            result = adder(result, it->callback(arguments...));
        }
        return result;
    }
    return default_value;
}

template <typename Result, typename... Arguments>
template <typename Object>
void Signal<Result(Arguments...)>::handle_signal_listener(CallbackData& callback_data, Object* object) noexcept {
    if constexpr (eastl::is_base_of<SignalListener, Object>::value) {
        SignalListener* signal_listener = static_cast<SignalListener*>(object);
#if defined(KW_DEBUG)
        for (auto* signal : signal_listener->m_signals) {
            KW_ASSERT(signal != this, "The same signal is added twice to the same object! "
                                      "This is probably not what you want!");
        }
#endif
        signal_listener->m_signals.push_back(this);

        callback_data.is_signal_listener = true;
        callback_data.object = static_cast<SignalListener*>(object);
    } else {
        callback_data.is_signal_listener = false;
        callback_data.object = object;
    }
}
} // namespace kw
