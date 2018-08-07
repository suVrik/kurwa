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

#include "c.h"

class B {
reflection public:
    int a;
    int b;
    int c;
private:
    int d;
    int e;
    int f;

    // Doesn't support 'reflection' simply by syntax.
//    struct {
//        int d2;
//        int e2;
//        int f2;
//    };
};

template <typename T>
class Tem {
reflection public:
    int ta;
    int tb;
    int tc;
};

namespace kw {
class C {
public:
    int a;
    int b;
    int c;

reflection private:
    int d;
    int e;
    int f;
};
} // namespace kw
