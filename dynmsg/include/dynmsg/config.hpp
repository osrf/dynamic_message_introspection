// Copyright 2021 Christophe Bedard
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DYNMSG__CONFIG_HPP_
#define DYNMSG__CONFIG_HPP_

// If DYNMSG_VALUE_ONLY is defined, the member's value will be used directly, e.g.
//    frame_id: "my_frame"
// instead of prodiving the type name as well as the value, e.g.
//    frame_id:
//      type: "string"
//      value: "my_frame"
// This also means that, with DYNMSG_VALUE_ONLY, the resulting
// YAML object can be converted back into a message.
#define DYNMSG_VALUE_ONLY

#endif  // DYNMSG__CONFIG_HPP_
