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
uint32 generate_unique_token() {
    static uint32 current_token = 0;
    return ++current_token;
}
} // namespace signal_details

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(Object* object, Result (Object::*const callback)(Arguments...)) {
    CallbackData data;
    data.callback = [object, callback](Arguments&&... arguments) {
        (object->*callback)(std::forward<Arguments>(arguments)...);
    };
    data.object = object;
    data.token = signal_details::generate_unique_token();
    callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object>
uint32 Signal<Result(Arguments...)>::connect(const Object* object, Result (Object::*const callback)(Arguments...) const) {
    CallbackData data;
    data.callback = [object, callback](Arguments&&... arguments) {
        (object->*callback)(std::forward<Arguments>(arguments)...);
    };
    data.object = object;
    data.token = signal_details::generate_unique_token();
    callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Object, typename Callback>
uint32 Signal<Result(Arguments...)>::connect(const Object* object, const Callback callback) {
    CallbackData data;
    data.callback = Function<Result(Arguments...)>(callback);
    data.object = object;
    data.token = signal_details::generate_unique_token();
    callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
template <typename Callback>
uint32 Signal<Result(Arguments...)>::connect(const Callback callback) {
    CallbackData data;
    data.callback = Function<Result(Arguments...)>(callback);
    data.object = nullptr;
    data.token = signal_details::generate_unique_token();
    callbacks.push_back(std::move(data));
    return data.token;
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::disconnect(const void* object) {
    for (auto it = callbacks.begin(); it != callbacks.end();) {
        if (it->object == object) {
            it = callbacks.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::disconnect(uint32 token) {
    for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
        if (it->token == token) {
            callbacks.erase(it);
            break;
        }
    }
}

template <typename Result, typename... Arguments>
void Signal<Result(Arguments...)>::emit(Arguments... arguments) {
    for (auto& callback : callbacks) {
        callback.callback(arguments...);
    }
}

template <typename Result, typename... Arguments>
template <typename Adder>
Result Signal<Result(Arguments...)>::emit(Arguments... arguments, const Adder adder) {
    if (!callbacks.empty()) {
        Result result = callbacks.front().callback(arguments...);
        for (auto it = ++callbacks.begin(); it != callbacks.end(); ++it) {
            result = adder(result, it->callback(arguments...));
        }
        return result;
    }
    return {};
}
} // namespace kw
