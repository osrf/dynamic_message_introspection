This document is a declaration of software quality for the `dynmsg_msgs` package, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# `dynmsg_msgs` Quality Declaration

The package `dynmsg_msgs` claims to be in the **Quality Level 2** category.

Below are the rationales, notes, and caveats for this claim, organized by each requirement listed in the [Package Requirements for Quality Level 2 in REP-2004](https://www.ros.org/reps/rep-2004.html).

## Version Policy [1]

### Version Scheme [1.i]

`dynmsg_msgs` uses `semver` according to the recommendation for ROS Core packages in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#versioning).

### Version Stability [1.ii]

`dynmsg_msgs` is at a stable version, i.e. `>= 1.0.0`.
The current version can be found in its [package.xml](package.xml).

### Public API Declaration [1.iii]

All message and service definition files located in `msg` and `srv` directories are considered part of the public API.

### API Stability Within a Released ROS Distribution [1.iv]/[1.vi]

`dynmsg_msgs` will not break public API within a released ROS distribution, i.e. no major releases once the ROS distribution is released.

### ABI Stability Within a Released ROS Distribution [1.v]/[1.vi]

`dynmsg_msgs` may break ABI within a released ROS distribution.

## Change Control Process [2]

`dynmsg_msgs` requires that all changes go through a pull request.
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

### Documentation Policy [2.v]

All pull requests must resolve related documentation changes before merging.

## Documentation

### Feature Documentation [3.i]

`dynmsg_msgs` has a list of provided [messages and services](README.md).
New messages and services require their own documentation in order to be added.

### Public API Documentation [3.ii]

`dynmsg_msgs` does not have public API documentation.

### License [3.iii]

The license for `dynmsg_msgs` is Apache 2.0, the type is declared in the [package.xml](package.xml) manifest file, and a full copy of the license is in the repository level [LICENSE](../LICENSE) file.

There is an automated test which runs a linter that ensures each file has a license statement.

### Copyright Statements [3.iv]

There are no currently copyrighted source files in this package.

## Testing [4]

### Feature Testing [4.i]

`dynmsg_msgs` is not directly tested.

### Public API Testing [4.ii]

`dynmsg_msgs` is not directly tested.

### Coverage [4.iii]

`dynmsg_msgs` does not currently track test coverage.

### Performance [4.iv]

`dynmsg_msgs` does not currently have performance tests.

### Linters and Static Analysis [4.v]

`dynmsg_msgs` uses and passes all the standard linters and static analysis tools for its generated C++ and Python code to ensure it follows the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#linters).

## Dependencies [5]

### Direct Runtime ROS Dependencies [5.i]/[5.ii]

`dynmsg_msgs` has the following runtime ROS dependencies, which are at or above Quality Level 2:
* `builtin_interfaces`: [QL 2](https://github.com/ros2/rcl_interfaces/tree/foxy/builtin_interfaces/QUALITY_DECLARATION.md)
* `rosidl_default_runtime` [QL 2](https://github.com/ros2/rosidl_defaults/tree/foxy/rosidl_default_runtime/QUALITY_DECLARATION.md)

It has several "buildtool" dependencies, which do not affect the resulting quality of the package, because they do not contribute to the public library API.

### Direct Runtime Non-ROS Dependencies [5.iii]

`dynmsg_msgs` does not have any runtime non-ROS dependencies.

## Platform Support [6]

`dynmsg_msgs` does not strictly support any platform.

## Security

### Vulnerability Disclosure Policy [7.i]

As a demonstration package, `dynmsg_msgs` does not have a vulnerability disclosure policy.
