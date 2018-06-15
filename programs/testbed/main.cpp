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

#include <algorithm>
#include <iostream>

int main(int argc, char* argv[]) {
    // This is to test C++17
    auto lambda = []() -> auto {
        return std::make_pair(13, 37);
    };
    auto [a, b] = lambda();
    std::cout << "testbed " << a << b << std::endl;
    return 0;
}
