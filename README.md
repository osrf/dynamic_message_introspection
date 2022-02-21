# dynamic_message_introspection

This repo demonstrates how to do introspection of C and C++ messages.
The [`dynmsg` package](./dynmsg) can convert ROS 2 messages into a YAML representation, and convert a YAML representation into ROS 2 messages.

The initial development of this code (with support for C messages) was graciously supported by [Rocos (@rocos.io)](https://www.rocos.io/).
C++ messages support was added by [Christophe Bédard](https://github.com/christophebedard).

The [`dynmsg_demo` package](./dynmsg_demo) contains a demonstration of how to do dynamic introspection of messages using the `rcl` message API.

## Examples

For a C message, see [`conversion.c`](./test_dynmsg/examples/conversion_c.cpp).
For a C++ message, see [`conversion.cpp`](./test_dynmsg/examples/conversion_cpp.cpp).

For more examples, see the [message conversion tests for `dynmsg`](./test_dynmsg/test/test_conversion.cpp).
