# `dynmsg_demo`

A demonstration of how to do dynamic introspection of messages using the `rcl` message API.
This code can convert any message from the in-memory representation into a YAML representation, and convert a YAML representation into the in-memory representation ready for use in client software and for sending via a topic.
All it needs is the compiled shared library that provides the message introspection information.
(For message types included in a ROS 2 distribution, these libraries are already provided by the distribution.)

## Quality Declaration

This package claims to be in the **Quality Level 4** category, see the [Quality Declaration](QUALITY_DECLARATION.md) for more details.
