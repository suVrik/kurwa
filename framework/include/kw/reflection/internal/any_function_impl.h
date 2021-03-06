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

#include <kw/reflection/any_function.h>

namespace kw {
namespace any_function_details {
template <typename... Arguments>
struct FunctionCaller;

template <typename Argument, typename... Arguments>
struct FunctionCaller<Argument, Arguments...> {
    template <typename Object, typename ObjectFunction, typename... UnpackedArguments>
    static Any call(Vector<Any>& arguments, Object* object, ObjectFunction function, UnpackedArguments&&... args);
};

template <>
struct FunctionCaller<> {
    template <typename Object, typename ObjectFunction, typename... UnpackedArguments>
    static Any call(Vector<Any>& arguments, Object* object, ObjectFunction function, UnpackedArguments&&... args) {
        if constexpr (eastl::is_same_v<decltype((object->*function)(eastl::forward<UnpackedArguments>(args)...)), void>) {
            (object->*function)(eastl::forward<UnpackedArguments>(args)...);
            return {}; // Return an empty any for 'void' functions
        } else {
            if constexpr (eastl::is_reference<decltype((object->*function)(eastl::forward<UnpackedArguments>(args)...))>::value) {
                // References are pointers in Type, Any and Reflection
                return Any(&(object->*function)(eastl::forward<UnpackedArguments>(args)...));
            } else {
                return (object->*function)(eastl::forward<UnpackedArguments>(args)...);
            }
        }
    }
};

template <typename Argument, typename... Arguments>
template <typename Object, typename ObjectFunction, typename... UnpackedArguments>
Any FunctionCaller<Argument, Arguments...>::call(Vector<Any>& arguments, Object* object, ObjectFunction function, UnpackedArguments&&... args) {
    Any argument = eastl::move(arguments[sizeof...(UnpackedArguments)]);
    if constexpr (eastl::is_reference<Argument>::value || eastl::is_rvalue_reference<Argument>::value) {
        KW_ASSERT(argument.is_same<typename eastl::remove_reference<Argument>::type*>(), "Wrong argument type!\nRequired: {}\nGot: {}",
                  typeid(typename eastl::remove_reference<Argument>::type*).name(), argument.get_type()->get_name());

        Argument argument_value = eastl::forward<Argument>(**argument.cast<typename eastl::remove_reference<Argument>::type*>());
        return FunctionCaller<Arguments...>::template call<Object, ObjectFunction, UnpackedArguments..., Argument>(arguments, object, function, eastl::forward<UnpackedArguments>(args)..., eastl::forward<Argument>(argument_value));
    } else {
        KW_ASSERT(argument.is_same<Argument>(), "Wrong argument type!\nRequired: {}\nGot: {}", typeid(Argument).name(),
                  argument.get_type()->get_name());

        Argument argument_value = eastl::forward<Argument>(*argument.cast<typename eastl::remove_reference<Argument>::type>());
        return FunctionCaller<Arguments...>::template call<Object, ObjectFunction, UnpackedArguments..., Argument>(arguments, object, function, eastl::forward<UnpackedArguments>(args)..., eastl::forward<Argument>(argument_value));
    }
}

template <typename Object, typename ObjectFunction, typename... Arguments>
Function<Any(const Any&, Vector<Any>&)> generate_function(const ObjectFunction function) noexcept {
    return [function](const Any& any_object, Vector<Any>& arguments) noexcept(false)->Any {
        Object* object = nullptr;

        // AnyFunction supports both self-contained Any's and pointer Any's
        if (any_object.get_type()->is_pointer()) {
            // We're not going to change the object ourselves anyway, so we can do a const_cast.
            object = const_cast<Object*>(any_object.cast_pointer<Object>());

            KW_ASSERT(object != nullptr, "Wrong object type!\nRequired: {}\nGot: {}", typeid(Object).name(),
                      any_object.get_type()->remove_pointer()->get_name());
        } else {
            // We're not going to change the object ourselves anyway, so we can do a const_cast.
            object = const_cast<Object*>(any_object.cast<Object>());

            KW_ASSERT(object != nullptr, "Wrong object type!\nRequired: {}\nGot: {}", typeid(Object).name(),
                      any_object.get_type()->get_name());
        }

        if (arguments.size() == sizeof...(Arguments)) {
            return FunctionCaller<Arguments...>::template call<Object, ObjectFunction>(arguments, object, function);
        } else {
            KW_ASSERT(false, "Invalid number of arguments!");

            return {};
        }
    };
}
} // namespace any_function_details

template <typename Result, typename Object, typename... Arguments>
AnyFunction::AnyFunction(Result (Object::*const function)(Arguments...)) noexcept {
    m_function = any_function_details::generate_function<Object, decltype(function), Arguments...>(function);
}

template <typename Result, typename Object, typename... Arguments>
AnyFunction::AnyFunction(Result (Object::*const function)(Arguments...) noexcept) noexcept {
    m_function = any_function_details::generate_function<Object, decltype(function), Arguments...>(function);
}

template <typename Result, typename Object, typename... Arguments>
AnyFunction::AnyFunction(Result (Object::*const function)(Arguments...) const) noexcept {
    m_function = any_function_details::generate_function<Object, decltype(function), Arguments...>(function);
}

template <typename Result, typename Object, typename... Arguments>
AnyFunction::AnyFunction(Result (Object::*const function)(Arguments...) const noexcept) noexcept {
    m_function = any_function_details::generate_function<Object, decltype(function), Arguments...>(function);
}

template <typename ObjectType, typename... Arguments>
Any AnyFunction::operator()(const ObjectType& object, Arguments&&... arguments) const noexcept(false) {
    KW_ASSERT(m_function, "AnyFunction is not initialized!");

    Vector<Any> any_arguments;
    any_arguments.reserve(sizeof...(arguments));
    (any_arguments.push_back(eastl::forward<Arguments>(arguments)), ...);
    return m_function(&object, any_arguments);
}

template <typename... Arguments>
Any AnyFunction::operator()(const Any& object, Arguments&&... arguments) const noexcept(false) {
    KW_ASSERT(m_function, "AnyFunction is not initialized!");

    Vector<Any> any_arguments;
    any_arguments.reserve(sizeof...(arguments));
    (any_arguments.push_back(eastl::forward<Arguments>(arguments)), ...);
    return m_function(object, any_arguments);
}
} // namespace kw
