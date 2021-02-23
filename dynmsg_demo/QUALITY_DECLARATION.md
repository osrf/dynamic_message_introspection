This document is a declaration of software quality for the `dynmsg_demo` package, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# dynmsg_demo Quality Declaration

The package `dynmsg_demo` claims to be in the **Quality Level 4** category.

Below are the rationales, notes, and caveats for this claim, organized by each requirement listed in the [Package Quality Categories in REP-2004](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#package-quality-categories) of the ROS2 developer guide.

## Version Policy [1]

### Version Scheme [1.i]

`dynmsg_demo` uses `semver` according to the recommendation for ROS Core packages in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#versioning).

### Version Stability [1.ii]

`dynmsg_demo` is at a stable version, i.e. `>= 1.0.0`.
The current version can be found in its [package.xml](package.xml), and its change history can be found in its [CHANGELOG](CHANGELOG.rst).

### Public API Declaration [1.iii]

All symbols in the installed headers are considered part of the public API.

Except for the exclusions listed below, all installed headers are in the `include` directory of the package, headers in any other folders are not installed and considered private.

### API Stability Policy [1.iv]

`dynmsg_demo` will not break public API within a released ROS distribution, i.e. no major releases once the ROS distribution is released.

### ABI Stability Policy [1.v]

`dynmsg_demo` may break ABI within a ROS distribution.

### ABI and ABI Stability Within a Released ROS Distribution [1.vi]

`dynmsg_demo` will not break API within a released ROS distribution, i.e. no major releases once the ROS distribution is released.
`dynmsg_demo` may break ABI within a released ROS distribution.

## Change Control Process [2]

`dynmsg_demo` requires that all changes go through a pull request.
The Developer Certificate of Origin (DCO) is enforced on pull requests.
A minimum of 1 approval from a fellow developer who did not author the pull request is required to consider it approved. Approval is required before merging.
Any required changes to documentation must be proposed before merging related changes.

### Change Requests [2.i]

All changes will occur through a pull request.

### Contributor Origin [2.ii]

This package uses DCO as its confirmation of contributor origin policy. More information can be found in [CONTRIBUTING](../CONTRIBUTING.md).

### Peer Review Policy [2.iii]

All pull requests will be peer-reviewed.

### Continuous Integration [2.iv]

All pull requests must pass CI.

###  Documentation Policy [2.v]

All pull requests must resolve related documentation changes before merging.

## Documentation [3]

### Feature Documentation [3.i]

`dynmsg_demo` does not have feature documentation.

### Public API Documentation [3.ii]

`dynmsg_demo` does not have public API documentation.

### License [3.iii]

The license for `dynmsg_demo` is Apache 2.0, and a summary is in each source file, the type is declared in the [`package.xml`](./package.xml) manifest file, and a full copy of the license is in the [`LICENSE`](../LICENSE) file.

There is an automated test which runs a linter that ensures each file has a license statement.

### Copyright Statements [3.iv]

The copyright holders each provide a statement of copyright in each source code file in `dynmsg_demo`.

There is an automated test which runs a linter that ensures each file has at least one copyright statement.

## Testing [4]

### Feature Testing [4.i]

`dynmsg_demo` has tests for all public API calls and unit tests for internal functions.
New features are required to have tests before being added.

### Public API Testing [4.ii]

Each part of the public API has tests, and new additions or changes to the public API require tests before being added.
The tests aim to cover both typical usage and corner cases, but are quantified by contributing to code coverage.

### Coverage [4.iii]

`dynmsg_demo` does not currently track test coverage.

### Performance [4.iv]

`dynmsg_demo` does not currently have performance tests.

### Linters and Static Analysis [4.v]

`dynmsg_demo` uses the ROS2 standard linters and static analysis tools for a C++ package as described in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#linters-and-static-analysis).
Passing implies there are no linter/static errors when testing against CI of supported platforms.
`dynmsg_demo` does not claim to pass the linters.

## Dependencies [5]

Below are evaluations of each of `dynmsg_demo`'s run-time and build-time dependencies that have been determined to influence the quality.

It has several "buildtool" dependencies, which do not affect the resulting quality of the package, because they do not contribute to the public library API.

It also has several test dependencies, which do not affect the resulting quality of the package, because they are only used to build and run the test code.

### Direct and Optional Runtime ROS Dependencies [5.i]/[5.ii]

`dynmsg_demo` has the following runtime ROS dependencies:

#### `rcl`

`rcl` a library to support implementation of language specific ROS 2 Client Libraries.

It is **Quality Level 3**, see its [Quality Declaration document](https://github.com/ros2/rcl/blob/foxy/rcl/QUALITY_DECLARATION.md).

#### `rcl_action`

`rcl_action` a library to support implementation of language specific ROS 2 Client Libraries.

It is **Quality Level 2**, see its [Quality Declaration document](https://github.com/ros2/rcl/blob/foxy/rcl/QUALITY_DECLARATION.md).

### Direct Runtime non-ROS Dependency [5.iii]

`dynmsg_demo` has the following runtime non-ROS dependencies.

#### `libyaml`

`libyaml` is a YAML parsing library written in C.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/libyaml_vendor/blob/foxy/libyaml_q_declaration.md).

## Platform Support [6]

`dynmsg_demo` does not strictly support any platform.

## Security

### Vulnerability Disclosure Policy [7.i]

As a demonstration package, `dynmsg_demo` does not have a vulnerability disclosure policy.
