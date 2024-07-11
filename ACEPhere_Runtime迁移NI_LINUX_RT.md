# 一、前言



NI LINUX RT系统默认时间会是2021年，导致编译安装会有时间警告，每次需要重新设置时间

```bash
sudo date -s "2024-07-10 15:57:00"
```



库的安装路径问题：直接在大目录/usr下查找可能查找不到库

```bash
$ ls /usr/local/lib64 | grep -Ein "zip"
2:libzip.so@
3:libzip.so.5@
4:libzip.so.5.5*
$ ls /usr/ | grep -Ein "zip"
```

常见的库的安装路径

```bash
/usr/lib
/usr/lib64
/usr/local/lib
/usr/local/lib64
```



opkg安装包

对应的是ipk的安装包





# 二、Celix迁移

针对celix框架移植到NI LINUX RT环境下查看是否可以正常编译运行

核心点：

1. 对Celix项目本身的支持
2. 对Celix依赖库的支持

以下是celix在ubuntu22.04环境下的依赖库安装，都是可以直接通过apt-get包管理器直接进行安装的

```bash
sudo apt-get install -yq --no-install-recommends \
    build-essential \
    git \
    curl \
    uuid-dev \
    libjansson-dev \
    libcurl4-openssl-dev \
    default-jdk \
    libffi-dev \
    libzip-dev \
    libxml2-dev \
    libczmq-dev \
    libcpputest-dev \
    rapidjson-dev
```

对比ubuntu22.04，在NI LINUX RT的包管理器是opkg



## 2.01 Celix



### 2.01.01 编译01

Celix的第一次cmake，在安装2.02 ~ 2.11的依赖以后执行

```bash
cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- The ASM compiler identification is GNU
-- Found assembler: /usr/bin/cc
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Using zip to create bundles
-- Found ZLIB: /usr/lib/libz.so (found version "1.2.11")
-- Found libuuid: /usr/lib/libuuid.so
-- Found CURL: /usr/lib/libcurl.so (found version "7.82.0")
-- Found libzip: /usr/local/lib64/libzip.so
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Performing Test LINKER_WRAP_SUPPORTED
-- Performing Test LINKER_WRAP_SUPPORTED - Success
-- Looking for open_memstream
-- Looking for open_memstream - found
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR - Success
-- Found libffi: /usr/lib/libffi.so
-- Found jansson: /usr/lib/libjansson.so
The Celix::Promises implementation is still experiment and the api and behaviour will probably still change.
-- Target architecture - x86_64
-- Enabling tests in the build - FALSE
-- Thread Stack Size - 102400
-- Enabling server executable - ON
-- Serve no static files - OFF
-- Disable CGI support - OFF
-- Disable caching support - OFF
-- C++ wrappers - OFF
-- IP Version 6 - OFF
-- Websockets support - TRUE
-- Server statistics support - OFF
-- Memory Debugging - OFF
-- ASAN in debug mode - ON
-- Force x32 / x64 architecture - OFF
-- Lua CGI support - OFF
-- zlib support - OFF
-- Executable installation - ON
-- Build if there are warnings - ON
-- Duktape CGI support - OFF
-- SSL support - ON
-- Compile for OpenSSL 1.0 API - OFF
-- Compile for OpenSSL 1.1 API - ON
-- Dynamically load SSL libraries - ON
-- SSL Library Name - libssl.so
-- SSL Cryptography Library Name - libcrypto.so
-- Configuring C Compiler
-- Performing Test NO_DIAGNOSTICS_PRODUCED
-- Performing Test NO_DIAGNOSTICS_PRODUCED - Failed
-- Performing Test -Wno-reserved-id-macros
-- Performing Test -Wno-reserved-id-macros - Failed
-- Could NOT find WinSock (missing: WINSOCK_LIBRARIES WINSOCK_INCLUDE_DIRS)
-- Found LibRt: /usr/lib/librt.so
-- Found LibDl: /usr/lib/libdl.a
CMake Warning at bundles/deployment_admin/CMakeLists.txt:20 (message):
  Celix::deployment_admin is considered unstable, because develop of this
  bundle has been dormant for a while


CMake Error at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
  Could NOT find LibXml2 (missing: LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR)
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:594 (_FPHSA_FAILURE_MESSAGE)
  /usr/share/cmake-3.22/Modules/FindLibXml2.cmake:108 (FIND_PACKAGE_HANDLE_STANDARD_ARGS)
  bundles/remote_services/discovery_common/CMakeLists.txt:20 (find_package)


-- Configuring incomplete, errors occurred!
See also "/home/admin/git_pro/acephere_runtime/thirdParty/celix/build/CMakeFiles/CMakeOutput.log".
See also "/home/admin/git_pro/acephere_runtime/thirdParty/celix/build/CMakeFiles/CMakeError.log".
admin@NI-cRIO-903x-VM-27e00187:~/git_pro/acephere_runtime/thirdParty/celix/build# ls /usr/lib | grep -Ein "xml2"
644:libxml2.so.2@
645:libxml2.so.2.9.14*
```

报错：Could NOT find LibXml2

但实际上libxml2这个库是有的，见2.06默认搜索查看的信息



### 2.01.02 编译02

在2.06中通过方案2（为解决），方案3（解决）后再次编译可以正常通过cmake

```bash
$ cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- The ASM compiler identification is GNU
-- Found assembler: /usr/bin/cc
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Using zip to create bundles
-- Found ZLIB: /usr/lib/libz.so (found version "1.2.11")
-- Found libuuid: /usr/lib/libuuid.so
-- Found CURL: /usr/lib/libcurl.so (found version "7.82.0")
-- Found libzip: /usr/local/lib64/libzip.so
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Performing Test LINKER_WRAP_SUPPORTED
-- Performing Test LINKER_WRAP_SUPPORTED - Success
-- Looking for open_memstream
-- Looking for open_memstream - found
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR - Success
-- Found libffi: /usr/lib/libffi.so
-- Found jansson: /usr/lib/libjansson.so
The Celix::Promises implementation is still experiment and the api and behaviour will probably still change.
-- Target architecture - x86_64
-- Enabling tests in the build - FALSE
-- Thread Stack Size - 102400
-- Enabling server executable - ON
-- Serve no static files - OFF
-- Disable CGI support - OFF
-- Disable caching support - OFF
-- C++ wrappers - OFF
-- IP Version 6 - OFF
-- Websockets support - TRUE
-- Server statistics support - OFF
-- Memory Debugging - OFF
-- ASAN in debug mode - ON
-- Force x32 / x64 architecture - OFF
-- Lua CGI support - OFF
-- zlib support - OFF
-- Executable installation - ON
-- Build if there are warnings - ON
-- Duktape CGI support - OFF
-- SSL support - ON
-- Compile for OpenSSL 1.0 API - OFF
-- Compile for OpenSSL 1.1 API - ON
-- Dynamically load SSL libraries - ON
-- SSL Library Name - libssl.so
-- SSL Cryptography Library Name - libcrypto.so
-- Configuring C Compiler
-- Performing Test NO_DIAGNOSTICS_PRODUCED
-- Performing Test NO_DIAGNOSTICS_PRODUCED - Failed
-- Performing Test -Wno-reserved-id-macros
-- Performing Test -Wno-reserved-id-macros - Failed
-- Could NOT find WinSock (missing: WINSOCK_LIBRARIES WINSOCK_INCLUDE_DIRS)
-- Found LibRt: /usr/lib/librt.so
-- Found LibDl: /usr/lib/libdl.a
CMake Warning at bundles/deployment_admin/CMakeLists.txt:20 (message):
  Celix::deployment_admin is considered unstable, because develop of this
  bundle has been dormant for a while


-- Found LibXml2: /usr/lib/libxml2.so (found version "2.9.14")
-- Found ZeroMQ: /usr/local/lib64/libzmq.so
-- Found czmq: /usr/local/lib/libczmq.so
-- Found RapidJSON: /usr/local/include/rapidjson
-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix/build

$ make
[  1%] Building C object examples/celix-examples/bundle_with_private_lib/CMakeFiles/tlib.dir/tlib/src/test.c.o
[  1%] Linking C shared library libtlib.so
[  1%] Built target tlib
[  1%] Building C object libs/utils/CMakeFiles/utils.dir/src/array_list.c.o
[  1%] Building C object libs/utils/CMakeFiles/utils.dir/src/hash_map.c.o
[  1%] Building C object libs/utils/CMakeFiles/utils.dir/src/linked_list.c.o
........（省略）...........
[ 99%] Built target create_framework_in_c
Scanning dependencies of target embedding
[ 99%] Building C object examples/celix-examples/embedding/CMakeFiles/embedding.dir/src/main.c.o
[ 99%] Building ASM object examples/celix-examples/embedding/CMakeFiles/embedding.dir/__/__/__/celix/gen/target/embedding/embed_bundle_apache_celix_c_shell.s.o
[100%] Building C object examples/celix-examples/embedding/CMakeFiles/embedding.dir/__/__/__/celix/gen/target/embedding/celix_embedded_bundles.c.o
[100%] Building ASM object examples/celix-examples/embedding/CMakeFiles/embedding.dir/__/__/__/celix/gen/target/embedding/embed_bundle_apache_celix_shell_tui.s.o
[100%] Linking C executable embedding
[100%] Built target embedding

$ sudo make install
Consolidate compiler generated dependencies of target tlib
[  1%] Built target tlib
Consolidate compiler generated dependencies of target utils
[  3%] Built target utils
Consolidate compiler generated dependencies of target framework
[  7%] Built target framework
Consolidate compiler generated dependencies of target hellotest
[  7%] Built target hellotest
[  7%] Built target hellotest_bundle
Consolidate compiler generated dependencies of target civetweb-c-library
........（省略）...........
Consolidate compiler generated dependencies of target civetweb_shared
[ 99%] Built target civetweb_shared
Consolidate compiler generated dependencies of target thpool
[ 99%] Built target thpool
Consolidate compiler generated dependencies of target create_framework_in_c
[ 99%] Built target create_framework_in_c
Consolidate compiler generated dependencies of target embedding
[100%] Built target embedding
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib64/libcelix_utils.so.2
-- Installing: /usr/local/lib64/libcelix_utils.so
-- Installing: /usr/local/include/celix/utils/
-- Installing: /usr/local/include/celix/utils//celix_utils.h
-- Installing: /usr/local/include/celix/utils//celix_string_hash_map.h
-- Installing: /usr/local/include/celix/utils//celix_filter.h
-- Installing: /usr/local/include/celix/utils//celix_version_range.h
-- Installing: /usr/local/include/celix/utils//celix_log_constants.h
-- Installing: /usr/local/include/celix/utils//celix_version.h
-- Installing: /usr/local/include/celix/utils//celix_properties.h
-- Installing: /usr/local/include/celix/utils//celix_convert_utils.h
-- Installing: /usr/local/include/celix/utils//celix_array_list.h
-- Installing: /usr/local/include/celix/utils//celix_build_assert.h
-- Installing: /usr/local/include/celix/utils//celix_errno.h
-- Installing: /usr/local/include/celix/utils//celix_threads.h
-- Installing: /usr/local/include/celix/utils//celix_hash_map_value.h
-- Installing: /usr/local/include/celix/utils//celix
-- Installing: /usr/local/include/celix/utils//celix/Exception.h
-- Installing: /usr/local/include/celix/utils//celix/Filter.h
-- Installing: /usr/local/include/celix/utils//celix/Utils.h
-- Installing: /usr/local/include/celix/utils//celix/Properties.h
-- Installing: /usr/local/include/celix/utils//celix_byteswap.h
-- Installing: /usr/local/include/celix/utils//celix_log_utils.h
-- Installing: /usr/local/include/celix/utils//celix_ref.h
-- Installing: /usr/local/include/celix/utils//celix_err.h
-- Installing: /usr/local/include/celix/utils//celix_log_level.h
-- Installing: /usr/local/include/celix/utils//celix_file_utils.h
-- Installing: /usr/local/include/celix/utils//celix_long_hash_map.h
-- Up-to-date: /usr/local/include/celix/utils/
-- Installing: /usr/local/include/celix/utils//celix_err_constants.h
-- Installing: /usr/local/include/celix/utils//celix_utils_export.h
-- Up-to-date: /usr/local/include/celix/utils
-- Installing: /usr/local/include/celix/utils/filter.h
-- Installing: /usr/local/include/celix/utils/array_list.h
-- Installing: /usr/local/include/celix/utils/ip_utils.h
-- Installing: /usr/local/include/celix/utils/utils.h
-- Installing: /usr/local/include/celix/utils/celixbool.h
-- Installing: /usr/local/include/celix/utils/version.h
-- Installing: /usr/local/include/celix/utils/celix_utils_api.h
-- Installing: /usr/local/include/celix/utils/exports.h
-- Installing: /usr/local/include/celix/utils/properties.h
-- Installing: /usr/local/include/celix/utils/hash_map.h
-- Installing: /usr/local/include/celix/utils/linked_list_iterator.h
-- Installing: /usr/local/include/celix/utils/version_range.h
-- Installing: /usr/local/include/celix/utils/linked_list.h
-- Installing: /usr/local/lib64/libcelix_dfi.so.1.1.0
-- Installing: /usr/local/lib64/libcelix_dfi.so.1
-- Set runtime path of "/usr/local/lib64/libcelix_dfi.so.1.1.0" to ""
-- Installing: /usr/local/lib64/libcelix_dfi.so
-- Installing: /usr/local/include/celix/dfi
-- Installing: /usr/local/include/celix/dfi/dyn_interface.h
-- Installing: /usr/local/include/celix/dfi/dfi_log_util.h
-- Installing: /usr/local/include/celix/dfi/dyn_message.h
-- Installing: /usr/local/include/celix/dfi/dyn_type.h
-- Installing: /usr/local/include/celix/dfi/avrobin_serializer.h
-- Installing: /usr/local/include/celix/dfi/json_serializer.h
-- Installing: /usr/local/include/celix/dfi/json_rpc.h
-- Installing: /usr/local/include/celix/dfi/dyn_common.h
-- Installing: /usr/local/include/celix/dfi/dyn_function.h
-- Up-to-date: /usr/local/include/celix/dfi
-- Installing: /usr/local/include/celix/dfi/celix_dfi_export.h
-- Installing: /usr/local/include/etcdlib
-- Installing: /usr/local/include/etcdlib/etcd.h
-- Installing: /usr/local/include/etcdlib/etcdlib.h
-- Up-to-date: /usr/local/include/etcdlib
-- Installing: /usr/local/include/etcdlib/etcdlib_export.h
-- Installing: /usr/local/lib64/libetcdlib.so.1.0.0
-- Installing: /usr/local/lib64/libetcdlib.so.1
-- Installing: /usr/local/lib64/libetcdlib.so
-- Installing: /usr/local/lib64/libcelix_etcdlib_static.a
-- Installing: /usr/local/include/celix/promises
-- Installing: /usr/local/include/celix/promises/celix
-- Installing: /usr/local/include/celix/promises/celix/impl
-- Installing: /usr/local/include/celix/promises/celix/impl/SharedPromiseState.h
-- Installing: /usr/local/include/celix/promises/celix/Deferred.h
-- Installing: /usr/local/include/celix/promises/celix/IScheduledExecutor.h
-- Installing: /usr/local/include/celix/promises/celix/DefaultExecutor.h
-- Installing: /usr/local/include/celix/promises/celix/RejectedExecutionException.h
-- Installing: /usr/local/include/celix/promises/celix/PromiseIllegalStateException.h
-- Installing: /usr/local/include/celix/promises/celix/PromiseInvocationException.h
-- Installing: /usr/local/include/celix/promises/celix/PromiseFactory.h
-- Installing: /usr/local/include/celix/promises/celix/IExecutor.h
-- Installing: /usr/local/include/celix/promises/celix/PromiseTimeoutException.h
-- Installing: /usr/local/include/celix/promises/celix/Promise.h
-- Installing: /usr/local/include/celix/promises/celix/DefaultScheduledExecutor.h
-- Installing: /usr/local/include/celix/pushstreams
-- Installing: /usr/local/include/celix/pushstreams/celix
-- Installing: /usr/local/include/celix/pushstreams/celix/impl
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/PushEventConsumer.h
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/UnbufferedPushStream.h
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/StreamPushEventConsumer.h
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/AbstractPushEventSource.h
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/IntermediatePushStream.h
-- Installing: /usr/local/include/celix/pushstreams/celix/impl/BufferedPushStream.h
-- Installing: /usr/local/include/celix/pushstreams/celix/IllegalStateException.h
-- Installing: /usr/local/include/celix/pushstreams/celix/IAutoCloseable.h
-- Installing: /usr/local/include/celix/pushstreams/celix/SynchronousPushEventSource.h
-- Installing: /usr/local/include/celix/pushstreams/celix/PushStreamProvider.h
-- Installing: /usr/local/include/celix/pushstreams/celix/IPushEventSource.h
-- Installing: /usr/local/include/celix/pushstreams/celix/AsynchronousPushEventSource.h
-- Installing: /usr/local/include/celix/pushstreams/celix/PushStream.h
-- Installing: /usr/local/include/celix/pushstreams/celix/IPushEventConsumer.h
-- Installing: /usr/local/include/celix/pushstreams/celix/PushEvent.h
-- Installing: /usr/local/lib64/libcelix_framework.so.2.3.0
-- Installing: /usr/local/lib64/libcelix_framework.so.2
-- Set runtime path of "/usr/local/lib64/libcelix_framework.so.2.3.0" to ""
-- Installing: /usr/local/lib64/libcelix_framework.so
-- Installing: /usr/local/include/celix/framework
-- Installing: /usr/local/include/celix/framework/celix_framework.h
-- Installing: /usr/local/include/celix/framework/celix_bundle_activator.h
-- Installing: /usr/local/include/celix/framework/celix_constants.h
-- Installing: /usr/local/include/celix/framework/celix_bundle_state.h
-- Installing: /usr/local/include/celix/framework/celix_service_listener.h
-- Installing: /usr/local/include/celix/framework/celix_dm_info.h
-- Installing: /usr/local/include/celix/framework/celix_types.h
-- Installing: /usr/local/include/celix/framework/celix_dm_component.h
-- Installing: /usr/local/include/celix/framework/celix_bundle_event.h
-- Installing: /usr/local/include/celix/framework/celix
-- Installing: /usr/local/include/celix/framework/celix/UseServiceBuilder.h
-- Installing: /usr/local/include/celix/framework/celix/Bundle.h
-- Installing: /usr/local/include/celix/framework/celix/FrameworkExceptions.h
-- Installing: /usr/local/include/celix/framework/celix/ServiceFactory.h
-- Installing: /usr/local/include/celix/framework/celix/Constants.h
-- Installing: /usr/local/include/celix/framework/celix/BundleContext.h
-- Installing: /usr/local/include/celix/framework/celix/BundleActivator.h
-- Installing: /usr/local/include/celix/framework/celix/ServiceRegistration.h
-- Installing: /usr/local/include/celix/framework/celix/ServiceRegistrationBuilder.h
-- Installing: /usr/local/include/celix/framework/celix/Framework.h
-- Installing: /usr/local/include/celix/framework/celix/TrackerBuilders.h
-- Installing: /usr/local/include/celix/framework/celix/FrameworkUtils.h
-- Installing: /usr/local/include/celix/framework/celix/dm
-- Installing: /usr/local/include/celix/framework/celix/dm/types.h
-- Installing: /usr/local/include/celix/framework/celix/dm/Component.h
-- Installing: /usr/local/include/celix/framework/celix/dm/DependencyManager.h
-- Installing: /usr/local/include/celix/framework/celix/dm/DependencyManagerInfo.h
-- Installing: /usr/local/include/celix/framework/celix/dm/ServiceDependency_Impl.h
-- Installing: /usr/local/include/celix/framework/celix/dm/ServiceDependency.h
-- Installing: /usr/local/include/celix/framework/celix/dm/DmActivator.h
-- Installing: /usr/local/include/celix/framework/celix/dm/ProvidedService_Impl.h
-- Installing: /usr/local/include/celix/framework/celix/dm/ProvidedService.h
-- Installing: /usr/local/include/celix/framework/celix/dm/Properties.h
-- Installing: /usr/local/include/celix/framework/celix/dm/Component_Impl.h
-- Installing: /usr/local/include/celix/framework/celix/dm/DependencyManager_Impl.h
-- Installing: /usr/local/include/celix/framework/celix/FrameworkFactory.h
-- Installing: /usr/local/include/celix/framework/celix/Trackers.h
-- Installing: /usr/local/include/celix/framework/celix_dependency_manager.h
-- Installing: /usr/local/include/celix/framework/celix_launcher.h
-- Installing: /usr/local/include/celix/framework/celix_service_event.h
-- Installing: /usr/local/include/celix/framework/celix_framework_factory.h
-- Installing: /usr/local/include/celix/framework/celix_bundle.h
-- Installing: /usr/local/include/celix/framework/celix_bundle_context.h
-- Installing: /usr/local/include/celix/framework/celix_service_factory.h
-- Installing: /usr/local/include/celix/framework/celix_framework_utils.h
-- Installing: /usr/local/include/celix/framework/celix_log.h
-- Installing: /usr/local/include/celix/framework/celix_api.h
-- Installing: /usr/local/include/celix/framework/celix_dm_service_dependency.h
-- Up-to-date: /usr/local/include/celix/framework
-- Installing: /usr/local/include/celix/framework/service_event.h
-- Installing: /usr/local/include/celix/framework/bundle_activator.h
-- Installing: /usr/local/include/celix/framework/dm_service_dependency.h
-- Installing: /usr/local/include/celix/framework/service_tracker.h
-- Installing: /usr/local/include/celix/framework/framework_event.h
-- Installing: /usr/local/include/celix/framework/bundle_archive.h
-- Installing: /usr/local/include/celix/framework/service_registration.h
-- Installing: /usr/local/include/celix/framework/bundle_revision.h
-- Installing: /usr/local/include/celix/framework/capability.h
-- Installing: /usr/local/include/celix/framework/module.h
-- Installing: /usr/local/include/celix/framework/service_registry.h
-- Installing: /usr/local/include/celix/framework/service_factory.h
-- Installing: /usr/local/include/celix/framework/bundle_state.h
-- Installing: /usr/local/include/celix/framework/framework_listener.h
-- Installing: /usr/local/include/celix/framework/listener_hook_service.h
-- Installing: /usr/local/include/celix/framework/dm_component.h
-- Installing: /usr/local/include/celix/framework/bundle.h
-- Installing: /usr/local/include/celix/framework/service_reference.h
-- Installing: /usr/local/include/celix/framework/framework.h
-- Installing: /usr/local/include/celix/framework/bundle_listener.h
-- Installing: /usr/local/include/celix/framework/requirement.h
-- Installing: /usr/local/include/celix/framework/framework_exports.h
-- Installing: /usr/local/include/celix/framework/dm_dependency_manager.h
-- Installing: /usr/local/include/celix/framework/dm_activator.h
-- Installing: /usr/local/include/celix/framework/bundle_context.h
-- Installing: /usr/local/include/celix/framework/wire.h
-- Installing: /usr/local/include/celix/framework/service_tracker_customizer.h
-- Installing: /usr/local/include/celix/framework/bundle_event.h
-- Installing: /usr/local/include/celix/framework/service_listener.h
-- Installing: /usr/local/include/celix/framework/archive.h
-- Installing: /usr/local/include/celix/framework/manifest.h
-- Up-to-date: /usr/local/include/celix/framework
-- Installing: /usr/local/include/celix/framework/celix_framework_export.h
-- Installing: /usr/local/bin/celix
-- Set runtime path of "/usr/local/bin/celix" to "/usr/local/lib64"
-- Installing: /usr/local/lib64/libdependency_manager_static.a
-- Installing: /usr/local/lib64/libdependency_manager_so.so
-- Set runtime path of "/usr/local/lib64/libdependency_manager_so.so" to ""
-- Installing: /usr/local/lib64/libcelix_dependency_manager_cxx_static.a
-- Installing: /usr/local/lib64/cmake/civetweb/civetweb-targets.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/civetweb-targets-noconfig.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/civetweb-config.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/civetweb-config-version.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/FindLibDl.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/FindLibRt.cmake
-- Installing: /usr/local/lib64/cmake/civetweb/FindWinSock.cmake
-- Installing: /usr/local/lib64/libcivetweb.so.1.15.0
-- Installing: /usr/local/lib64/libcivetweb.so
-- Installing: /usr/local/include/civetweb.h
-- Installing: /usr/local/bin/civetweb
-- Set runtime path of "/usr/local/bin/civetweb" to ""
-- Installing: /usr/local/lib64/libcivetweb_shared.so
-- Installing: /usr/local/include/celix/http_admin
-- Installing: /usr/local/include/celix/http_admin/http_admin
-- Installing: /usr/local/include/celix/http_admin/http_admin/api.h
-- Installing: /usr/local/include/celix/http_admin/http_admin/websocket_admin_service.h
-- Installing: /usr/local/include/celix/http_admin/http_admin/http_admin_service.h
-- Installing: /usr/local/include/celix/http_admin/http_admin/http_admin_info_service.h
-- Installing: /usr/local/share/celix/bundles/celix_http_admin.zip
-- Installing: /usr/local/include/celix/log_service
-- Installing: /usr/local/include/celix/log_service/log_listener.h
-- Installing: /usr/local/include/celix/log_service/log_service.h
-- Installing: /usr/local/include/celix/log_service/log_reader_service.h
-- Installing: /usr/local/include/celix/log_service/log_entry.h
-- Up-to-date: /usr/local/include/celix/log_service
-- Installing: /usr/local/include/celix/log_service/celix_log_service.h
-- Installing: /usr/local/include/celix/log_service/celix_log_control.h
-- Installing: /usr/local/include/celix/log_service/celix_log_sink.h
-- Installing: /usr/local/include/celix/log_helper
-- Installing: /usr/local/include/celix/log_helper/log_helper.h
-- Installing: /usr/local/lib64/libcelix_log_utils.a
-- Up-to-date: /usr/local/include/celix/log_helper
-- Installing: /usr/local/include/celix/log_helper/celix
-- Installing: /usr/local/include/celix/log_helper/celix/LogHelper.h
-- Installing: /usr/local/include/celix/log_helper/celix_log_helper.h
-- Installing: /usr/local/share/celix/bundles/celix_log_service.zip
-- Installing: /usr/local/share/celix/bundles/celix_log_writer_stdout.zip
-- Installing: /usr/local/share/celix/bundles/celix_log_admin.zip
-- Installing: /usr/local/share/celix/bundles/celix_syslog_writer.zip
-- Installing: /usr/local/include/celix/shell
-- Installing: /usr/local/include/celix/shell/shell_constants.h
-- Installing: /usr/local/include/celix/shell/shell.h
-- Installing: /usr/local/include/celix/shell/command.h
-- Up-to-date: /usr/local/include/celix/shell
-- Installing: /usr/local/include/celix/shell/celix
-- Installing: /usr/local/include/celix/shell/celix/IShellCommand.h
-- Installing: /usr/local/include/celix/shell/celix_shell_constants.h
-- Installing: /usr/local/include/celix/shell/celix_shell.h
-- Installing: /usr/local/include/celix/shell/celix_shell_command.h
-- Installing: /usr/local/share/celix/bundles/celix_shell.zip
-- Installing: /usr/local/share/celix/bundles/celix_ShellCxx.zip
-- Installing: /usr/local/share/celix/bundles/celix_shell_tui.zip
-- Installing: /usr/local/share/celix/bundles/celix_shell_wui.zip
-- Installing: /usr/local/share/celix/bundles/celix_remote_shell.zip
-- Installing: /usr/local/include/celix/deployment_admin
-- Installing: /usr/local/include/celix/deployment_admin/resource_processor.h
-- Installing: /usr/local/share/celix/bundles/deployment_admin.zip
-- Installing: /usr/local/include/celix/remote_service_admin
-- Installing: /usr/local/include/celix/remote_service_admin/remote_constants.h
-- Installing: /usr/local/include/celix/rsa
-- Installing: /usr/local/include/celix/rsa/remote_interceptors_handler.h
-- Installing: /usr/local/include/celix/rsa/remote_endpoint.h
-- Installing: /usr/local/include/celix/rsa/rsa_request_handler_service.h
-- Installing: /usr/local/include/celix/rsa/remote_endpoint_impl.h
-- Installing: /usr/local/include/celix/rsa/import_registration.h
-- Installing: /usr/local/include/celix/rsa/rsa_request_sender_service.h
-- Installing: /usr/local/include/celix/rsa/remote_proxy.h
-- Installing: /usr/local/include/celix/rsa/remote_interceptor.h
-- Installing: /usr/local/include/celix/rsa/remote_constants.h
-- Installing: /usr/local/include/celix/rsa/rsa_rpc_factory.h
-- Installing: /usr/local/include/celix/rsa/endpoint_description.h
-- Installing: /usr/local/include/celix/rsa/endpoint_listener.h
-- Installing: /usr/local/include/celix/rsa/remote_service_admin.h
-- Installing: /usr/local/include/celix/rsa/export_registration.h
-- Installing: /usr/local/lib64/libcelix_rsa_common.a
-- Installing: /usr/local/lib64/libcelix_rsa_dfi_utils.a
-- Installing: /usr/local/include/celix/rsa_dfi_utils
-- Installing: /usr/local/include/celix/rsa_dfi_utils/dfi_utils.h
-- Installing: /usr/local/share/celix/bundles/rsa_discovery.zip
-- Installing: /usr/local/share/celix/bundles/rsa_discovery_etcd.zip
-- Installing: /usr/local/share/celix/bundles/rsa_topology_manager.zip
-- Installing: /usr/local/share/celix/bundles/rsa_dfi.zip
-- Installing: /usr/local/share/celix/bundles/rsa_json_rpc.zip
-- Installing: /usr/local/include/celix/pubsub
-- Installing: /usr/local/include/celix/pubsub/pubsub
-- Installing: /usr/local/include/celix/pubsub/pubsub/api.h
-- Installing: /usr/local/include/celix/pubsub/pubsub/publisher.h
-- Installing: /usr/local/include/celix/pubsub/pubsub/subscriber.h
-- Installing: /usr/local/lib64/libcelix_pubsub_utils.a
-- Installing: /usr/local/include/celix/pubsub_utils
-- Installing: /usr/local/include/celix/pubsub_utils/pubsub_matching.h
-- Installing: /usr/local/include/celix/pubsub_utils/pubsub_serialization_provider.h
-- Installing: /usr/local/include/celix/pubsub_utils/pubsub_utils_url.h
-- Installing: /usr/local/include/celix/pubsub_utils/pubsub_utils.h
-- Installing: /usr/local/include/celix/pubsub_utils/pubsub_serializer_handler.h
-- Installing: /usr/local/lib64/libcelix_pubsub_spi.a
-- Installing: /usr/local/include/celix/pubsub_spi
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_listeners.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_admin.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_endpoint.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_interceptor.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_admin_metrics.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_interceptors_handler.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_serializer.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_constants.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_message_serialization_service.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_protocol.h
-- Installing: /usr/local/include/celix/pubsub_spi/pubsub_message_serialization_marker.h
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_topology_manager.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_admin_zmq.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_admin_tcp.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_admin_udp_multicast.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_admin_websocket.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_discovery_etcd.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_serializer_json.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_serializer_avrobin.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_protocol_wire_v1.zip
-- Installing: /usr/local/share/celix/bundles/celix_pubsub_protocol_wire_v2.zip
-- Up-to-date: /usr/local/include/celix/rsa
-- Installing: /usr/local/include/celix/rsa/celix
-- Installing: /usr/local/include/celix/rsa/celix/rsa
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IEndpointAnnouncer.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/RemoteConstants.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IImportServiceFactory.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/RemoteServicesException.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/EndpointDescription.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IExportedService.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IImportRegistration.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IExportServiceFactory.h
-- Installing: /usr/local/include/celix/rsa/celix/rsa/IExportRegistration.h
-- Installing: /usr/local/share/celix/bundles/Celix_RemoteServiceAdmin.zip
-- Installing: /usr/local/share/celix/bundles/celix_RsaConfiguredDiscovery.zip
-- Installing: /usr/local/share/celix/cmake/Targets.cmake
-- Installing: /usr/local/share/celix/cmake/Targets-noconfig.cmake
-- Installing: /usr/local/share/celix/cmake/CelixTargets-NOCONFIG.cmake
-- Installing: /usr/local/share/celix/cmake/CelixTargets.cmake
-- Installing: /usr/local/share/celix/cmake/Modules
-- Installing: /usr/local/share/celix/cmake/Modules/FindNanoMsg.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/Findlibffi.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/FindCppUTest.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/Findlibuuid.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/FindZeroMQ.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/FindRapidJSON.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/Findjansson.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/Findczmq.cmake
-- Installing: /usr/local/share/celix/cmake/Modules/Findlibzip.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix
-- Installing: /usr/local/share/celix/cmake/cmake_celix/Runtimes.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/UseCelix.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/BundlePackaging.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/templates
-- Installing: /usr/local/share/celix/cmake/cmake_celix/templates/embed_bundle_linux.s
-- Installing: /usr/local/share/celix/cmake/cmake_celix/templates/embed_bundle_apple.s
-- Installing: /usr/local/share/celix/cmake/cmake_celix/templates/NOTE
-- Installing: /usr/local/share/celix/cmake/cmake_celix/templates/Manifest.in
-- Installing: /usr/local/share/celix/cmake/cmake_celix/ContainerPackaging.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/runtime_start.sh.in
-- Installing: /usr/local/share/celix/cmake/cmake_celix/DockerPackaging.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/create_target_filesystem.sh
-- Installing: /usr/local/share/celix/cmake/cmake_celix/Generic.cmake
-- Installing: /usr/local/share/celix/cmake/cmake_celix/runtime_stop.sh.in
-- Installing: /usr/local/share/celix/cmake/cmake_celix/runtime_common.sh.in
-- Installing: /usr/local/share/celix/cmake/CelixDeps.cmake
-- Installing: /usr/local/lib64/cmake/Celix/CelixConfig.cmake
-- Installing: /usr/local/lib64/cmake/Celix/CelixConfigVersion.cmake
```





## 2.02 git

本身就有

```bash
# 查看安装的git版本
$ git --version
git version 2.35.7
```





## 2.03 curl

本身就有

`curl` 是一个非常强大且常用的命令行工具和库，用于传输数据。它支持多种协议，包括 HTTP、HTTPS、FTP 等

```bash
# 查看安装的curl版本
$ curl --version
curl 7.82.0 (x86_64-nilrt-linux-gnu) libcurl/7.82.0 OpenSSL/3.0.12 zlib/1.2.11 libidn2/2.3.2
Release-Date: 2022-03-05
Protocols: file ftp ftps http https
Features: alt-svc AsynchDNS Debug HSTS HTTPS-proxy IDN IPv6 Largefile libz NTLM SSL TLS-SRP UnixSockets
```





## 2.04 libjansson-dev

`libjansson-dev` 是一个开发包，它包含了 `Jansson` 库的头文件和开发文档。`Jansson` 是一个C语言的库，用于解析、生成和操作JSON数据。安装 `libjansson-dev` 可以让你在C项目中使用这个库来处理JSON

```bash
$ sudo opkg install libjansson-dev
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/extra/core2-64/libjansson-lic_2.13.1-r0.17_core2-64.ipk.
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/extra/core2-64/libjansson4_2.13.1-r0.17_core2-64.ipk.
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/extra/core2-64/libjansson-dev_2.13.1-r0.17_core2-64.ipk.
Installing libjansson-lic (2.13.1) on root
Installing libjansson4 (2.13.1) on root
Installing libjansson-dev (2.13.1) on root
Configuring libjansson-lic.
Configuring libjansson4.
Configuring libjansson-dev.

# 实际在/usr/lib下查看到的版本
$ ls /usr/lib | grep -Ein "jansson"
357:libjansson.so@
358:libjansson.so.4@
359:libjansson.so.4.13.0*
```





## 2.05 libffi-dev

`libffi-dev` 是 `libffi` (Foreign Function Interface) 库的开发包。`libffi` 库允许你在运行时调用和使用动态生成的函数调用。这在需要调用外部库的函数，尤其是那些使用不同编程语言编写的库时非常有用

```bash
# 默认也有这个库，暂时先不安装
$ ls /usr/lib | grep -Ein "ffi"
206:libffi.so@
207:libffi.so.8@
208:libffi.so.8.1.2*
```





## 2.06 libxml2-dev

`libxml2-dev` 是针对 `libxml2` 库的开发包，它包含了头文件和静态库，用于开发需要使用 XML 解析和操作的应用程序。`libxml2` 是一个功能强大且广泛使用的开源 XML 库，提供了一系列 API 来解析、验证、创建和操作 XML 文档。



方案1：

```bash
# 默认也有这个库，暂时先不安装
$ ls /usr/lib | grep -Ein "xml"
640:libxml2.so.2@
641:libxml2.so.2.9.14*
```



方案2

对于找不到的问题从大小写重定向名字

```bash
$ cd /usr/lib
$ ls -la | grep -Ein "xml"
$ ln -s libxml2.so.2.9.14 LibXml2.so
# 重定向成功了
$ ls -la | grep -Ein "xml"
647:lrwxrwxrwx  1 admin administrators       17 Jul 11 09:54 LibXml2.so -> libxml2.so.2.9.14*
648:lrwxrwxrwx  1 admin administrators       17 Mar  9  2018 libxml2.so.2 -> libxml2.so.2.9.14*
649:-rwxr-xr-x  1 admin administrators  1399056 Mar  9  2018 libxml2.so.2.9.14*
```

但实际celix使用cmake时依旧报错



方案3：只有xml2的库却没有对应的头文件

```bash
$ ls -la /usr/include | grep -Ein "xml2"
admin@NI-cRIO-903x-VM-27e00187:~/git_pro/acephere_runtime/thirdParty/celix/build#
```

直接通过opkg下载安装（先把之间创建的软连接LibXml2.so删除还原）

```bash
$ sudo opkg install libxml2-dev
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/main/core2-64/libxml2-dev_2.9.14-r0.71_core2-64.ipk.
Installing libxml2-dev (2.9.14) on root
Configuring libxml2-dev.

# 查看库文件发现没什么变化只有在/usr/lib下存在so库，查看头文件发现的确在"/usr/include"目录下多了"libxml2"目录
$ ls -la /usr/include | grep -Ein "xml2"
126:drwxr-xr-x  3 admin administrators   4096 May  2  2022 libxml2/
```





## 2.07 libzip-dev

`libzip-dev` 是 `libzip` 库的开发包，它包含了用于开发和编译需要使用 ZIP 格式文件压缩和解压功能的应用程序所需的头文件和静态库。

```bash
# 默认不存在这个库
$ ls /usr | grep -Ein "zip"

# opkg包管理器中也没有这个库
$ sudo opkg install libzip-dev
 * opkg_prepare_url_for_install: Couldn't find anything to satisfy 'libzip-dev'.
```

手动下载安装，下载地址

```http
https://libzip.org/download/
```

编译安装

```bash
$ mkdir build

$ cd build

$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/libzip-1.10.1/build

$ cmake ..
-- The C compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Looking for include file CommonCrypto/CommonCrypto.h
-- Looking for include file CommonCrypto/CommonCrypto.h - not found
-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
-- Could NOT find Nettle: Found unsuitable version ".", but required is at least "3.0" (found /usr/lib/libnettle.so)
-- Found GnuTLS: /usr/lib/libgnutls.so
-- Could NOT find MbedTLS (missing: MbedTLS_LIBRARY MbedTLS_INCLUDE_DIR) (Required is at least version "1.0")
-- Found OpenSSL: /usr/lib/libcrypto.so (found version "3.0.12")
........（省略）...........
-- Looking for getopt - found
CMake Warning at CMakeLists.txt:318 (message):
  -- nihtest not found, regression testing disabled


-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/libzip-1.10.1/build

$ make
[  0%] Generating zip_err_str.c
[  1%] Building C object lib/CMakeFiles/zip.dir/zip_add.c.o
[  1%] Building C object lib/CMakeFiles/zip.dir/zip_add_dir.c.o
[  1%] Building C object lib/CMakeFiles/zip.dir/zip_add_entry.c.o
[  1%] Building C object lib/CMakeFiles/zip.dir/zip_algorithm_deflate.c.o
[  1%] Building C object lib/CMakeFiles/zip.dir/zip_buffer.c.o
[  3%] Building C object lib/CMakeFiles/zip.dir/zip_close.c.o
........（省略）...........
[ 95%] Generating ziptool.html
[ 95%] Built target man
[ 95%] Building C object src/CMakeFiles/zipcmp.dir/zipcmp.c.o
[ 96%] Building C object src/CMakeFiles/zipcmp.dir/diff_output.c.o
[ 96%] Linking C executable zipcmp
[ 96%] Built target zipcmp
[ 96%] Building C object src/CMakeFiles/zipmerge.dir/zipmerge.c.o
[ 96%] Linking C executable zipmerge
[ 96%] Built target zipmerge
[ 96%] Building C object src/CMakeFiles/ziptool.dir/ziptool.c.o
[ 98%] Linking C executable ziptool
[ 98%] Built target ziptool
[ 98%] Building C object examples/CMakeFiles/add-compressed-data.dir/add-compressed-data.c.o
[ 98%] Linking C executable add-compressed-data
[ 98%] Built target add-compressed-data
[ 98%] Building C object examples/CMakeFiles/autoclose-archive.dir/autoclose-archive.c.o
[ 98%] Linking C executable autoclose-archive
[ 98%] Built target autoclose-archive
[ 98%] Building C object examples/CMakeFiles/in-memory.dir/in-memory.c.o
[100%] Linking C executable in-memory
[100%] Built target in-memory

$ sudo make install
Consolidate compiler generated dependencies of target zip
[ 35%] Built target zip
[ 95%] Built target man
Consolidate compiler generated dependencies of target zipcmp
[ 96%] Built target zipcmp
Consolidate compiler generated dependencies of target zipmerge
[ 96%] Built target zipmerge
Consolidate compiler generated dependencies of target ziptool
[ 98%] Built target ziptool
Consolidate compiler generated dependencies of target add-compressed-data
[ 98%] Built target add-compressed-data
Consolidate compiler generated dependencies of target autoclose-archive
[ 98%] Built target autoclose-archive
Consolidate compiler generated dependencies of target in-memory
[100%] Built target in-memory
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib64/pkgconfig/libzip.pc
-- Installing: /usr/local/lib64/cmake/libzip/modules/FindNettle.cmake
-- Installing: /usr/local/lib64/cmake/libzip/modules/Findzstd.cmake
-- Installing: /usr/local/lib64/cmake/libzip/modules/FindMbedTLS.cmake
-- Installing: /usr/local/include/zipconf.h
-- Installing: /usr/local/lib64/cmake/libzip/libzip-config.cmake
-- Installing: /usr/local/lib64/cmake/libzip/libzip-config-version.cmake
-- Installing: /usr/local/lib64/cmake/libzip/libzip-targets.cmake
-- Installing: /usr/local/lib64/cmake/libzip/libzip-targets-noconfig.cmake
-- Installing: /usr/local/lib64/libzip.so.5.5
-- Installing: /usr/local/lib64/libzip.so.5
-- Installing: /usr/local/lib64/libzip.so
-- Installing: /usr/local/include/zip.h
-- Installing: /usr/local/share/doc/libzip/libzip/ZIP_SOURCE_GET_ARGS.html
-- Installing: /usr/local/share/doc/libzip/libzip/libzip.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_add.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_add_dir.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_close.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_compression_method_supported.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_delete.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_dir_add.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_discard.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_encryption_method_supported.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_clear.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_code_system.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_code_zip.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_fini.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_get.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_get_sys_type.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_init.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_set.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_strerror.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_system_type.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_to_data.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_to_str.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_errors.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fclose.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fdopen.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_add.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_attributes_init.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_field_delete.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_field_get.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_field_set.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_fields_count.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_get_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_get_error.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_get_external_attributes.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_rename.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_set_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_set_encryption.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_set_external_attributes.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_set_mtime.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_strerror.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fopen.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fopen_encrypted.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fread.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fseek.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_ftell.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_archive_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_archive_flag.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_error.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_file_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_name.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_num_entries.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_get_num_files.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_libzip_version.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_name_locate.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_open.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_register_cancel_callback_with_state.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_register_progress_callback.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_register_progress_callback_with_state.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_rename.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_set_archive_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_set_archive_flag.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_set_default_password.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_set_file_comment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_set_file_compression.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_begin_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_buffer.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_buffer_fragment.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_close.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_commit_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_error.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_file.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_filep.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_free.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_function.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_is_deleted.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_is_seekable.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_layered.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_keep.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_make_command_bitmap.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_open.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_read.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_rollback_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_seek.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_seek_compute_offset.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_seek_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_stat.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_tell.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_tell_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32a.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32handle.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32w.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_window_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_write.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_zip.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_zip_file.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_stat.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_stat_init.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_unchange.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_unchange_all.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_unchange_archive.html
-- Installing: /usr/local/share/doc/libzip/libzip/zipcmp.html
-- Installing: /usr/local/share/doc/libzip/libzip/zipmerge.html
-- Installing: /usr/local/share/doc/libzip/libzip/ziptool.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_replace.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_error_clear.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_error_get.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_error_init_with_code.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_replace.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_field_delete_by_id.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_field_get_by_id.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_extra_fields_count_by_id.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_set_dostime.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_strerror.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fopen_index.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_fopen_index_encrypted.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_file_is_seekable.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_open_from_source.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_begin_write_cloning.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_buffer_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_buffer_fragment_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_file_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_filep_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_function_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_layered_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32a_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32handle_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_win32w_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_zip_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_source_zip_file_create.html
-- Installing: /usr/local/share/doc/libzip/libzip/zip_stat_index.html
-- Installing: /usr/local/bin/zipcmp
-- Set runtime path of "/usr/local/bin/zipcmp" to ""
-- Installing: /usr/local/bin/zipmerge
-- Set runtime path of "/usr/local/bin/zipmerge" to ""
-- Installing: /usr/local/bin/ziptool
-- Set runtime path of "/usr/local/bin/ziptool" to ""

# 查看安装的库
$ ls /usr/local/lib64 | grep -Ein "zip"
2:libzip.so@
3:libzip.so.5@
4:libzip.so.5.5*
```





## 2.08 libcpputest-dev

`libcpputest-dev` 是用于开发的 `CppUTest` 库的 Debian/Ubuntu 系统的开发包。`CppUTest` 是一个用于 C/C++ 单元测试的轻量级框架，它基于 `JUnit`（Java 的单元测试框架）的设计理念，专门用于嵌入式和桌面应用程序的单元测试

查找库都不存在

```bash
$ ls /usr/lib | grep "cpputest"
$ ls /usr/lib64/ | grep "cpputest"
$ ls /usr/local/lib | grep "cpputest"
$ ls /usr/local/lib64 | grep "cpputest"
```

包管理器也没有这个包

```bash
$ sudo opkg install libcpputest-dev
 * opkg_prepare_url_for_install: Couldn't find anything to satisfy 'libcpputest-dev'.
```

下载地址，下载的是`Download Release 3.8 as .tar.gz`

```bash
https://cpputest.github.io/
```

编译安装

```bash
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8

$ mkdir build

$ cd build/

# cmake找不到g++(具体解决方案见"问题记录" -> "Cmake找到g++"")
$ cmake ..
-- The CXX compiler identification is unknown
CMake Error at CMakeLists.txt:1 (project):
  No CMAKE_CXX_COMPILER could be found.

  Tell CMake where to find the compiler by setting either the environment
  variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path
  to the compiler, or to the compiler name if it is in the PATH.


-- Configuring incomplete, errors occurred!

# 解决后再次使用cmake正常
$ cmake ..
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at CMakeLists.txt:7 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Looking for fork
-- Looking for fork - found
-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
-- Performing Test WARNING_C_FLAG_Weverything
-- Performing Test WARNING_C_FLAG_Weverything - Failed
-- Performing Test WARNING_C_FLAG_Wall
-- Performing Test WARNING_C_FLAG_Wall - Success
-- Performing Test WARNING_C_FLAG_Wextra
-- Performing Test WARNING_C_FLAG_Wextra - Success
-- Performing Test WARNING_C_FLAG_Wshadow
-- Performing Test WARNING_C_FLAG_Wshadow - Success
-- Performing Test WARNING_C_FLAG_Wswitch-default
-- Performing Test WARNING_C_FLAG_Wswitch-default - Success
-- Performing Test WARNING_C_FLAG_Wswitch-enum
-- Performing Test WARNING_C_FLAG_Wswitch-enum - Success
-- Performing Test WARNING_C_FLAG_Wconversion
-- Performing Test WARNING_C_FLAG_Wconversion - Success
-- Performing Test WARNING_C_FLAG_Wsign-conversion
-- Performing Test WARNING_C_FLAG_Wsign-conversion - Success
-- Performing Test WARNING_C_FLAG_Wno-padded
-- Performing Test WARNING_C_FLAG_Wno-padded - Success
-- Performing Test WARNING_C_FLAG_Wno-disabled-macro-expansion
-- Performing Test WARNING_C_FLAG_Wno-disabled-macro-expansion - Failed
-- Performing Test WARNING_C_FLAG_Wno-reserved-id-macro
-- Performing Test WARNING_C_FLAG_Wno-reserved-id-macro - Failed
-- Performing Test WARNING_C_FLAG_Wno-keyword-macro
-- Performing Test WARNING_C_FLAG_Wno-keyword-macro - Failed
-- Performing Test WARNING_C_FLAG_Wno-long-long
-- Performing Test WARNING_C_FLAG_Wno-long-long - Success
-- Performing Test WARNING_C_FLAG_Wstrict-prototypes
-- Performing Test WARNING_C_FLAG_Wstrict-prototypes - Success
-- Performing Test WARNING_CXX_FLAG_TO_CHECK
-- Performing Test WARNING_CXX_FLAG_TO_CHECK - Failed

-------------------------------------------------------
CppUTest Version 3.8

Current compiler options:
    CC:                                 /usr/bin/cc
    CXX:                                /usr/bin/g++
    CppUTest CFLAGS:                     -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"  -Wall -Wextra -Wshadow -Wswitch-default -Wswitch-enum -Wconversion -Wsign-conversion -Wno-padded -Wno-long-long -Wstrict-prototypes
    CppUTest CXXFLAGS:                   -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h" -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"
    CppUTest LDFLAGS:

Features configured in CppUTest:
    Memory Leak Detection:              ON
    Compiling Extensions:               ON
    Support Long Long:                  OFF
    Use CppUTest flags:                 ON

    Using Standard C library:           ON
    Using Standard C++ library:         ON
    Using C++11 library:                OFF

    Generating map file:                OFF
    Compiling with coverage:            OFF

    Compile and run self-tests          ON
    Run self-tests separately           OFF

-------------------------------------------------------

-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/build

$ make
CMake Deprecation Warning at CMakeLists.txt:7 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)

-------------------------------------------------------
CppUTest Version 3.8

Current compiler options:
    CC:                                 /usr/bin/cc
    CXX:                                /usr/bin/g++
    CppUTest CFLAGS:                     -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"  -Wall -Wextra -Wshadow -Wswitch-default -Wswitch-enum -Wconversion -Wsign-conversion -Wno-padded -Wno-long-long -Wstrict-prototypes
    CppUTest CXXFLAGS:                   -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h" -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"
    CppUTest LDFLAGS:

Features configured in CppUTest:
    Memory Leak Detection:              ON
    Compiling Extensions:               ON
    Support Long Long:                  OFF
    Use CppUTest flags:                 ON

    Using Standard C library:           ON
    Using Standard C++ library:         ON
    Using C++11 library:                OFF

    Generating map file:                OFF
    Compiling with coverage:            OFF

    Compile and run self-tests          ON
    Run self-tests separately           OFF

-------------------------------------------------------

-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/build
make[2]: Warning: File '../src/CppUTest/CommandLineArguments.cpp' has modification time 111060656 s in the future
[  1%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/CommandLineArguments.cpp.o
........（省略）...........
[ 98%] Building CXX object tests/CppUTestExt/CMakeFiles/CppUTestExtTests.dir/OrderedTestTest.cpp.o
[100%] Linking CXX executable CppUTestExtTests
Discovering Tests in CppUTestExtTests
TestGroup: TestOrderedTestMacros
TestGroup: TestOrderedTest
TestGroup: MockReturnValueTest
TestGroup: MockStrictOrderTest
TestGroup: MockSupport_c
TestGroup: MockSupportTestWithFixture
TestGroup: MockSupportTest
TestGroup: MockPlugin
TestGroup: MockParameterTest
TestGroup: ComparatorsAndCopiersRepository
TestGroup: MockHierarchyTest
TestGroup: MockFailureTest
TestGroup: MockExpectedCallsList
TestGroup: MockIgnoredExpectedCall
TestGroup: MockExpectedCallComposite
TestGroup: MockExpectedCall
TestGroup: MockNamedValueHandlerRepository
TestGroup: MockComparatorCopierTest
TestGroup: MockCallTest
TestGroup: MockCheatSheet
TestGroup: MockCheckedActualCall
TestGroup: NormalMemoryReportFormatter
TestGroup: MemoryReporterPlugin
TestGroup: MemoryReportAllocator
TestGroup: IEEE754ExceptionsPlugin2
TestGroup: FE__with_Plugin
TestGroup: CodeMemoryReportFormatter
make[2]: warning:  Clock skew detected.  Your build may be incomplete.
[100%] Built target CppUTestExtTests

$ sudo make install
CMake Deprecation Warning at CMakeLists.txt:7 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)

-------------------------------------------------------
CppUTest Version 3.8

Current compiler options:
    CC:                                 /usr/bin/cc
    CXX:                                /usr/bin/g++
    CppUTest CFLAGS:                     -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"  -Wall -Wextra -Wshadow -Wswitch-default -Wswitch-enum -Wconversion -Wsign-conversion -Wno-padded -Wno-long-long -Wstrict-prototypes
    CppUTest CXXFLAGS:                   -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h" -include "/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/include/CppUTest/MemoryLeakDetectorMallocMacros.h"
    CppUTest LDFLAGS:

Features configured in CppUTest:
    Memory Leak Detection:              ON
    Compiling Extensions:               ON
    Support Long Long:                  OFF
    Use CppUTest flags:                 ON

    Using Standard C library:           ON
    Using Standard C++ library:         ON
    Using C++11 library:                OFF

    Generating map file:                OFF
    Compiling with coverage:            OFF

    Compile and run self-tests          ON
    Run self-tests separately           OFF

-------------------------------------------------------

-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/build
Consolidate compiler generated dependencies of target CppUTest
make[2]: Warning: File '../src/CppUTest/CommandLineArguments.cpp' has modification time 111060543 s in the future
[  1%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/CommandLineArguments.cpp.o
[  2%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/MemoryLeakWarningPlugin.cpp.o
[  3%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/TestHarness_c.cpp.o
[  4%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/TestRegistry.cpp.o
[  5%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/CommandLineTestRunner.cpp.o
[  6%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/SimpleString.cpp.o
[  7%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/TestMemoryAllocator.cpp.o
[  8%] Building CXX object src/CppUTest/CMakeFiles/CppUTest.dir/TestResult.cpp.o
........（省略）...........
TestGroup: CodeMemoryReportFormatter
make[2]: warning:  Clock skew detected.  Your build may be incomplete.
[100%] Built target CppUTestExtTests
Install the project...
-- Install configuration: "RelWithDebInfo"
-- Installing: /usr/local/lib/pkgconfig/cpputest.pc
-- Installing: /usr/local/include/CppUTest/CppUTestGeneratedConfig.h
-- Installing: /usr/local/lib/CppUTest/cmake/CppUTestConfig.cmake
-- Installing: /usr/local/lib/CppUTest/cmake/CppUTestConfigVersion.cmake
-- Installing: /usr/local/lib/CppUTest/cmake/CppUTestTargets.cmake
-- Installing: /usr/local/lib/CppUTest/cmake/CppUTestTargets-relwithdebinfo.cmake
-- Installing: /usr/local/include/CppUTest/CommandLineArguments.h
-- Installing: /usr/local/include/CppUTest/PlatformSpecificFunctions.h
-- Installing: /usr/local/include/CppUTest/TestMemoryAllocator.h
-- Installing: /usr/local/include/CppUTest/CommandLineTestRunner.h
-- Installing: /usr/local/include/CppUTest/PlatformSpecificFunctions_c.h
-- Installing: /usr/local/include/CppUTest/TestOutput.h
-- Installing: /usr/local/include/CppUTest/CppUTestConfig.h
-- Installing: /usr/local/include/CppUTest/SimpleString.h
-- Installing: /usr/local/include/CppUTest/TestPlugin.h
-- Installing: /usr/local/include/CppUTest/JUnitTestOutput.h
-- Installing: /usr/local/include/CppUTest/TeamCityTestOutput.h
-- Installing: /usr/local/include/CppUTest/StandardCLibrary.h
-- Installing: /usr/local/include/CppUTest/TestRegistry.h
-- Installing: /usr/local/include/CppUTest/MemoryLeakDetector.h
-- Installing: /usr/local/include/CppUTest/TestFailure.h
-- Installing: /usr/local/include/CppUTest/TestResult.h
-- Installing: /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h
-- Installing: /usr/local/include/CppUTest/TestFilter.h
-- Installing: /usr/local/include/CppUTest/TestTestingFixture.h
-- Installing: /usr/local/include/CppUTest/MemoryLeakDetectorNewMacros.h
-- Installing: /usr/local/include/CppUTest/TestHarness.h
-- Installing: /usr/local/include/CppUTest/Utest.h
-- Installing: /usr/local/include/CppUTest/MemoryLeakWarningPlugin.h
-- Installing: /usr/local/include/CppUTest/TestHarness_c.h
-- Installing: /usr/local/include/CppUTest/UtestMacros.h
-- Installing: /usr/local/lib/libCppUTest.a
-- Installing: /usr/local/include/CppUTestExt/CodeMemoryReportFormatter.h
-- Installing: /usr/local/include/CppUTestExt/IEEE754ExceptionsPlugin.h
-- Installing: /usr/local/include/CppUTestExt/MemoryReportAllocator.h
-- Installing: /usr/local/include/CppUTestExt/MockExpectedCall.h
-- Installing: /usr/local/include/CppUTestExt/MockCheckedExpectedCall.h
-- Installing: /usr/local/include/CppUTestExt/MockExpectedCallsList.h
-- Installing: /usr/local/include/CppUTestExt/MockSupportPlugin.h
-- Installing: /usr/local/include/CppUTestExt/MemoryReportFormatter.h
-- Installing: /usr/local/include/CppUTestExt/MockFailure.h
-- Installing: /usr/local/include/CppUTestExt/MockSupport.h
-- Installing: /usr/local/include/CppUTestExt/MockSupport_c.h
-- Installing: /usr/local/include/CppUTestExt/GMock.h
-- Installing: /usr/local/include/CppUTestExt/GTest.h
-- Installing: /usr/local/include/CppUTestExt/MemoryReporterPlugin.h
-- Installing: /usr/local/include/CppUTestExt/OrderedTest.h
-- Installing: /usr/local/include/CppUTestExt/GTestConvertor.h
-- Installing: /usr/local/include/CppUTestExt/MockActualCall.h
-- Installing: /usr/local/include/CppUTestExt/MockCheckedActualCall.h
-- Installing: /usr/local/include/CppUTestExt/MockNamedValue.h
-- Up-to-date: /usr/local/include/CppUTestExt/MockSupport.h
-- Installing: /usr/local/lib/libCppUTestExt.a

# 查看安装所在路径
$ ls -la /usr/local/lib | grep -Ein "cpputest"
4:drwxr-xr-x 3 admin administrators    4096 Jan  1 00:43 CppUTest/
5:-rw-r--r-- 1 admin administrators  546948 Jan  1 00:42 libCppUTest.a
6:-rw-r--r-- 1 admin administrators  568322 Jan  1 00:42 libCppUTestExt.a
```





## 2.09 rapidjson-dev

`rapidjson-dev` 是指为开发者提供的 RapidJSON 库的开发包（development package）。RapidJSON 是一个快速的 C++ JSON 解析器/生成器，旨在提供高效的 JSON 数据处理能力

查找库都不存在

```bash
$ ls /usr/lib | grep "rapidjson"
$ ls /usr/lib64/ | grep "rapidjson"
$ ls /usr/local/lib | grep "rapidjson"
$ ls /usr/local/lib64 | grep "rapidjson"
```

包管理器也没有这个包

```bash
$ sudo opkg install rapidjson-dev
 * opkg_prepare_url_for_install: Couldn't find anything to satisfy 'rapidjson-dev'.
```

下载地址（选择下载的是master最新版本，非release）

```http
https://github.com/Tencent/rapidjson
```

编译安装

```bash
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/rapidjson

$ mkdir build

$ cd build/

$ cmake ..
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE)
-- No Doxygen found. Documentation won't be built
CMake Deprecation Warning at example/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Could NOT find GTestSrc (missing: GTEST_SOURCE_DIR GTEST_INCLUDE_DIR)
-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/rapidjson/build

$ make
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE)
-- No Doxygen found. Documentation won't be built
CMake Deprecation Warning at example/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Could NOT find GTestSrc (missing: GTEST_SOURCE_DIR GTEST_INCLUDE_DIR)
-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/rapidjson/build
make[2]: Warning: File '../example/archiver/archiver.cpp' has modification time 111059910 s in the future
[  2%] Building CXX object example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o
[  5%] Building CXX object example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o
........（省略）...........
[ 79%] Built target simplereader
[ 82%] Building CXX object example/CMakeFiles/simplepullreader.dir/simplepullreader/simplepullreader.cpp.o
[ 84%] Linking CXX executable ../bin/simplepullreader
[ 84%] Built target simplepullreader
[ 87%] Building CXX object example/CMakeFiles/simplewriter.dir/simplewriter/simplewriter.cpp.o
[ 89%] Linking CXX executable ../bin/simplewriter
[ 89%] Built target simplewriter
[ 92%] Building CXX object example/CMakeFiles/sortkeys.dir/sortkeys/sortkeys.cpp.o
[ 94%] Linking CXX executable ../bin/sortkeys
[ 94%] Built target sortkeys
[ 97%] Building CXX object example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o
[100%] Linking CXX executable ../bin/tutorial
[100%] Built target tutorial
[100%] Built target examples

$ sudo make install
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE)
-- No Doxygen found. Documentation won't be built
CMake Deprecation Warning at example/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Could NOT find GTestSrc (missing: GTEST_SOURCE_DIR GTEST_INCLUDE_DIR)
-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/rapidjson/build
Consolidate compiler generated dependencies of target archivertest
[  2%] Building CXX object example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o
[  5%] Building CXX object example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o
........（省略）...........
[ 69%] Built target serialize
Consolidate compiler generated dependencies of target simpledom
[ 74%] Built target simpledom
Consolidate compiler generated dependencies of target simplereader
[ 79%] Built target simplereader
Consolidate compiler generated dependencies of target simplepullreader
[ 84%] Built target simplepullreader
Consolidate compiler generated dependencies of target simplewriter
[ 89%] Built target simplewriter
Consolidate compiler generated dependencies of target sortkeys
[ 94%] Built target sortkeys
Consolidate compiler generated dependencies of target tutorial
[100%] Built target tutorial
[100%] Built target examples
Install the project...
-- Install configuration: "RelWithDebInfo"
-- Installing: /usr/local/lib/pkgconfig/RapidJSON.pc
-- Installing: /usr/local/share/doc/RapidJSON/readme.md
-- Installing: /usr/local/include/rapidjson
-- Installing: /usr/local/include/rapidjson/encodings.h
-- Installing: /usr/local/include/rapidjson/document.h
-- Installing: /usr/local/include/rapidjson/stringbuffer.h
-- Installing: /usr/local/include/rapidjson/stream.h
-- Installing: /usr/local/include/rapidjson/encodedstream.h
-- Installing: /usr/local/include/rapidjson/pointer.h
-- Installing: /usr/local/include/rapidjson/fwd.h
-- Installing: /usr/local/include/rapidjson/filereadstream.h
-- Installing: /usr/local/include/rapidjson/memorybuffer.h
-- Installing: /usr/local/include/rapidjson/ostreamwrapper.h
-- Installing: /usr/local/include/rapidjson/writer.h
-- Installing: /usr/local/include/rapidjson/internal
-- Installing: /usr/local/include/rapidjson/internal/itoa.h
-- Installing: /usr/local/include/rapidjson/internal/diyfp.h
-- Installing: /usr/local/include/rapidjson/internal/stack.h
-- Installing: /usr/local/include/rapidjson/internal/clzll.h
-- Installing: /usr/local/include/rapidjson/internal/ieee754.h
-- Installing: /usr/local/include/rapidjson/internal/strtod.h
-- Installing: /usr/local/include/rapidjson/internal/strfunc.h
-- Installing: /usr/local/include/rapidjson/internal/swap.h
-- Installing: /usr/local/include/rapidjson/internal/pow10.h
-- Installing: /usr/local/include/rapidjson/internal/dtoa.h
-- Installing: /usr/local/include/rapidjson/internal/regex.h
-- Installing: /usr/local/include/rapidjson/internal/meta.h
-- Installing: /usr/local/include/rapidjson/internal/biginteger.h
-- Installing: /usr/local/include/rapidjson/uri.h
-- Installing: /usr/local/include/rapidjson/reader.h
-- Installing: /usr/local/include/rapidjson/allocators.h
-- Installing: /usr/local/include/rapidjson/cursorstreamwrapper.h
-- Installing: /usr/local/include/rapidjson/filewritestream.h
-- Installing: /usr/local/include/rapidjson/error
-- Installing: /usr/local/include/rapidjson/error/en.h
-- Installing: /usr/local/include/rapidjson/error/error.h
-- Installing: /usr/local/include/rapidjson/memorystream.h
-- Installing: /usr/local/include/rapidjson/istreamwrapper.h
-- Installing: /usr/local/include/rapidjson/rapidjson.h
-- Installing: /usr/local/include/rapidjson/prettywriter.h
-- Installing: /usr/local/include/rapidjson/msinttypes
-- Installing: /usr/local/include/rapidjson/msinttypes/stdint.h
-- Installing: /usr/local/include/rapidjson/msinttypes/inttypes.h
-- Installing: /usr/local/include/rapidjson/schema.h
-- Installing: /usr/local/share/doc/RapidJSON/examples
-- Installing: /usr/local/share/doc/RapidJSON/examples/jsonx
-- Installing: /usr/local/share/doc/RapidJSON/examples/jsonx/jsonx.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/CMakeLists.txt
-- Installing: /usr/local/share/doc/RapidJSON/examples/pretty
-- Installing: /usr/local/share/doc/RapidJSON/examples/pretty/pretty.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/messagereader
-- Installing: /usr/local/share/doc/RapidJSON/examples/messagereader/messagereader.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/filterkeydom
-- Installing: /usr/local/share/doc/RapidJSON/examples/filterkeydom/filterkeydom.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/condense
-- Installing: /usr/local/share/doc/RapidJSON/examples/condense/condense.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/schemavalidator
-- Installing: /usr/local/share/doc/RapidJSON/examples/schemavalidator/schemavalidator.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/filterkey
-- Installing: /usr/local/share/doc/RapidJSON/examples/filterkey/filterkey.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/tutorial
-- Installing: /usr/local/share/doc/RapidJSON/examples/tutorial/tutorial.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplepullreader
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplepullreader/simplepullreader.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/lookaheadparser
-- Installing: /usr/local/share/doc/RapidJSON/examples/lookaheadparser/lookaheadparser.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/capitalize
-- Installing: /usr/local/share/doc/RapidJSON/examples/capitalize/capitalize.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/parsebyparts
-- Installing: /usr/local/share/doc/RapidJSON/examples/parsebyparts/parsebyparts.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/prettyauto
-- Installing: /usr/local/share/doc/RapidJSON/examples/prettyauto/prettyauto.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/serialize
-- Installing: /usr/local/share/doc/RapidJSON/examples/serialize/serialize.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/traverseaspointer.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/archiver
-- Installing: /usr/local/share/doc/RapidJSON/examples/archiver/archiver.h
-- Installing: /usr/local/share/doc/RapidJSON/examples/archiver/archiver.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/archiver/archivertest.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplewriter
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplewriter/simplewriter.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/simpledom
-- Installing: /usr/local/share/doc/RapidJSON/examples/simpledom/simpledom.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplereader
-- Installing: /usr/local/share/doc/RapidJSON/examples/simplereader/simplereader.cpp
-- Installing: /usr/local/share/doc/RapidJSON/examples/sortkeys
-- Installing: /usr/local/share/doc/RapidJSON/examples/sortkeys/sortkeys.cpp
-- Installing: /usr/local/lib/cmake/RapidJSON/RapidJSONConfig.cmake
-- Up-to-date: /usr/local/lib/cmake/RapidJSON/RapidJSONConfig.cmake
-- Installing: /usr/local/lib/cmake/RapidJSON/RapidJSONConfigVersion.cmake
-- Installing: /usr/local/lib/cmake/RapidJSON/RapidJSON-targets.cmake

# 查看安装结果
结果并没有生成对用的so文件
```





## 2.10 libczmq-dev

`libczmq-dev` 是 ZeroMQ 的 C 风格高层 API 库的开发包（development package）。它提供了开发 ZeroMQ 应用程序所需的头文件和静态库或动态链接库，使开发者能够方便地使用 ZeroMQ 提供的高级通信功能。

查找库都不存在

```bash
$ ls /usr/lib | grep -Ein "czmq"
$ ls /usr/lib64/ | grep -Ein "czmq"
$ ls /usr/local/lib | grep -Ein "czmq"
$ ls /usr/local/lib64 | grep -Ein "czmq"
```

包管理器也没有这个包

```bash
$ sudo opkg install libczmq-dev
 * opkg_prepare_url_for_install: Couldn't find anything to satisfy 'libczmq-dev'.
```

下载地址（最终使用的是release版本zeromq-4.3.5）

```http
https://github.com/zeromq/libzmq
```

编译安装

```bash
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/czmq-4.2.1

$ mkdir build

$ cd build

# cmake报错，还额外依赖libzmq（跳转到2.09.01的解决）
$ cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- git workspace root [0]: /home/admin/git_pro/acephere_runtime
-- Looking for linux/wireless.h
-- Looking for linux/wireless.h - found
-- Looking for net/if_media.h
-- Looking for net/if_media.h - not found
-- Looking for getifaddrs
-- Looking for getifaddrs - found
-- Looking for freeifaddrs
-- Looking for freeifaddrs - found
-- Looking for include files sys/socket.h, net/if.h
-- Looking for include files sys/socket.h, net/if.h - found
-- Looking for AI_V4MAPPED
-- Looking for AI_V4MAPPED - not found
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (libzmq).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findlibzmq.cmake:7 (include)
  CMakeLists.txt:133 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (LIBZMQ)
  does not match the name of the calling package (libzmq).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findlibzmq.cmake:83 (find_package_handle_standard_args)
  CMakeLists.txt:133 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find LIBZMQ (missing: LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS)
CMake Error at CMakeLists.txt:144 (message):
  libzmq not found.
  
  # 解决后继续cmake .. 虽然有警告，但总体是通过了
  cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- git workspace root [0]: /home/admin/git_pro/acephere_runtime
-- Looking for linux/wireless.h
-- Looking for linux/wireless.h - found
-- Looking for net/if_media.h
-- Looking for net/if_media.h - not found
-- Looking for getifaddrs
-- Looking for getifaddrs - found
-- Looking for freeifaddrs
-- Looking for freeifaddrs - found
-- Looking for include files sys/socket.h, net/if.h
-- Looking for include files sys/socket.h, net/if.h - found
-- Looking for AI_V4MAPPED
-- Looking for AI_V4MAPPED - not found
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (libzmq).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findlibzmq.cmake:7 (include)
  CMakeLists.txt:133 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (LIBZMQ)
  does not match the name of the calling package (libzmq).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findlibzmq.cmake:83 (find_package_handle_standard_args)
  CMakeLists.txt:133 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found LIBZMQ: /usr/local/lib64/libzmq.so
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (uuid).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Finduuid.cmake:7 (include)
  CMakeLists.txt:150 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (UUID) does
  not match the name of the calling package (uuid).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Finduuid.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:150 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found UUID: /usr/lib/libuuid.so
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (systemd).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findsystemd.cmake:7 (include)
  CMakeLists.txt:168 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (SYSTEMD)
  does not match the name of the calling package (systemd).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findsystemd.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:168 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find SYSTEMD (missing: SYSTEMD_LIBRARIES SYSTEMD_INCLUDE_DIRS)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (lz4).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findlz4.cmake:7 (include)
  CMakeLists.txt:186 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (LZ4) does
  not match the name of the calling package (lz4).  This can lead to problems
  in calling code that expects `find_package` result variables (e.g.,
  `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findlz4.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:186 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find LZ4 (missing: LZ4_LIBRARIES LZ4_INCLUDE_DIRS)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (libcurl).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findlibcurl.cmake:7 (include)
  CMakeLists.txt:204 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (LIBCURL)
  does not match the name of the calling package (libcurl).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findlibcurl.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:204 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found LIBCURL: /usr/lib/libcurl.so
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (nss).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findnss.cmake:7 (include)
  CMakeLists.txt:222 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (NSS) does
  not match the name of the calling package (nss).  This can lead to problems
  in calling code that expects `find_package` result variables (e.g.,
  `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  Findnss.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:222 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find NSS (missing: NSS_LIBRARIES NSS_INCLUDE_DIRS)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (PkgConfig)
  does not match the name of the calling package (libmicrohttpd).  This can
  lead to problems in calling code that expects `find_package` result
  variables (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:99 (find_package_handle_standard_args)
  Findlibmicrohttpd.cmake:7 (include)
  CMakeLists.txt:240 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning (dev) at /usr/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args`
  (LIBMICROHTTPD) does not match the name of the calling package
  (libmicrohttpd).  This can lead to problems in calling code that expects
  `find_package` result variables (e.g., `_FOUND`) to follow a certain
  pattern.
Call Stack (most recent call first):
  Findlibmicrohttpd.cmake:34 (find_package_handle_standard_args)
  CMakeLists.txt:240 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found LIBMICROHTTPD: /usr/lib/libmicrohttpd.so
-- Detected CZMQ Version - 4.2.1
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Checking whether SOCK_CLOEXEC is supported
-- Performing Test CZMQ_HAVE_SOCK_CLOEXEC
-- Performing Test CZMQ_HAVE_SOCK_CLOEXEC - Success

-- ******************* Configuration Summary *******************
-- General:
--   Version           :   4.2.1
--   System            :   Linux
--   C compiler        :   /usr/bin/cc
--   Debug C flags     :   -g  -std=gnu99 -DCZMQ_HAVE_SOCK_CLOEXEC=1
--   Release C flags   :   -O3  -std=gnu99 -DCZMQ_HAVE_SOCK_CLOEXEC=1
--   Build type        :   Debug
--   Static build      :   ON
--   Shared build      :   ON
--   Draft API         :   Yes
--
-- Dependencies:
-- The following OPTIONAL packages have been found:

 * uuid
 * libcurl
 * libmicrohttpd
 * Threads

-- The following REQUIRED packages have been found:

 * libzmq

-- The following OPTIONAL packages have not been found:

 * systemd
 * lz4
 * nss

--
-- Install:
--   Install prefix    :/usr/local
--
-- ************************* Options ***************************
-- Options:
--   Use the Draft API (default = yes):
--   -DENABLE-DRAFTS=[yes|no]
--
-- *************************************************************
-- Configuration complete! Now procced with:
--   'make'                 compile the project
--   'make test'            run the project's selftest
--   'make install'         install the project to /usr/local
--
-- Further options are:
--   'ctest -V              run test with verbose logging
--   'ctest -R <test_name>' run a specific test
--   'ctest -T memcheck'    run the project's selftest with
--                          valgrind to check for memory leaks
--
-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/czmq-4.2.1/build

$ make
[  1%] Building C object CMakeFiles/czmq_objects.dir/src/zactor.c.o
[  3%] Building C object CMakeFiles/czmq_objects.dir/src/zarmour.c.o
[  5%] Building C object CMakeFiles/czmq_objects.dir/src/zcert.c.o
[  7%] Building C object CMakeFiles/czmq_objects.dir/src/zcertstore.c.o
[  9%] Building C object CMakeFiles/czmq_objects.dir/src/zchunk.c.o
[ 11%] Building C object CMakeFiles/czmq_objects.dir/src/zclock.c.o
[ 13%] Building C object CMakeFiles/czmq_objects.dir/src/zconfig.c.o
[ 15%] Building C object CMakeFiles/czmq_objects.dir/src/zdigest.c.o
[ 17%] Building C object CMakeFiles/czmq_objects.dir/src/zdir.c.o
[ 19%] Building C object CMakeFiles/czmq_objects.dir/src/zdir_patch.c.o
[ 21%] Building C object CMakeFiles/czmq_objects.dir/src/zfile.c.o
[ 23%] Building C object CMakeFiles/czmq_objects.dir/src/zframe.c.o
[ 25%] Building C object CMakeFiles/czmq_objects.dir/src/zhash.c.o
[ 26%] Building C object CMakeFiles/czmq_objects.dir/src/zhashx.c.o
[ 28%] Building C object CMakeFiles/czmq_objects.dir/src/ziflist.c.o
[ 30%] Building C object CMakeFiles/czmq_objects.dir/src/zlist.c.o
[ 32%] Building C object CMakeFiles/czmq_objects.dir/src/zlistx.c.o
[ 34%] Building C object CMakeFiles/czmq_objects.dir/src/zloop.c.o
[ 36%] Building C object CMakeFiles/czmq_objects.dir/src/zmsg.c.o
[ 38%] Building C object CMakeFiles/czmq_objects.dir/src/zpoller.c.o
[ 40%] Building C object CMakeFiles/czmq_objects.dir/src/zsock.c.o
[ 42%] Building C object CMakeFiles/czmq_objects.dir/src/zstr.c.o
[ 44%] Building C object CMakeFiles/czmq_objects.dir/src/zsys.c.o
[ 46%] Building C object CMakeFiles/czmq_objects.dir/src/zuuid.c.o
[ 48%] Building C object CMakeFiles/czmq_objects.dir/src/zauth.c.o
[ 50%] Building C object CMakeFiles/czmq_objects.dir/src/zbeacon.c.o
[ 51%] Building C object CMakeFiles/czmq_objects.dir/src/zgossip.c.o
[ 53%] Building C object CMakeFiles/czmq_objects.dir/src/zmonitor.c.o
[ 55%] Building C object CMakeFiles/czmq_objects.dir/src/zproxy.c.o
[ 57%] Building C object CMakeFiles/czmq_objects.dir/src/zrex.c.o
[ 59%] Building C object CMakeFiles/czmq_objects.dir/src/zgossip_msg.c.o
[ 61%] Building C object CMakeFiles/czmq_objects.dir/src/zargs.c.o
[ 63%] Building C object CMakeFiles/czmq_objects.dir/src/zproc.c.o
[ 65%] Building C object CMakeFiles/czmq_objects.dir/src/ztimerset.c.o
[ 67%] Building C object CMakeFiles/czmq_objects.dir/src/ztrie.c.o
[ 69%] Building C object CMakeFiles/czmq_objects.dir/src/zhttp_client.c.o
[ 71%] Building C object CMakeFiles/czmq_objects.dir/src/zhttp_server.c.o
[ 73%] Building C object CMakeFiles/czmq_objects.dir/src/zhttp_server_options.c.o
[ 75%] Building C object CMakeFiles/czmq_objects.dir/src/zhttp_request.c.o
[ 76%] Building C object CMakeFiles/czmq_objects.dir/src/zhttp_response.c.o
[ 78%] Building C object CMakeFiles/czmq_objects.dir/src/zosc.c.o
[ 80%] Building C object CMakeFiles/czmq_objects.dir/src/czmq_private_selftest.c.o
[ 80%] Built target czmq_objects
[ 82%] Linking C shared library libczmq.so
[ 82%] Built target czmq
[ 84%] Linking C static library libczmq.a
[ 84%] Built target czmq-static
[ 86%] Building C object CMakeFiles/zmakecert.dir/src/zmakecert.c.o
[ 88%] Linking C executable zmakecert
[ 88%] Built target zmakecert
[ 90%] Building C object CMakeFiles/zsp.dir/src/zsp.c.o
[ 92%] Linking C executable zsp
[ 92%] Built target zsp
[ 94%] Building C object CMakeFiles/test_randof.dir/src/test_randof.c.o
[ 96%] Linking C executable test_randof
[ 96%] Built target test_randof
[ 98%] Building C object CMakeFiles/czmq_selftest.dir/src/czmq_selftest.c.o
[100%] Linking C executable czmq_selftest
[100%] Built target czmq_selftest
[100%] Built target copy-selftest-ro
[100%] Built target make-selftest-rw

$ sudo make install
Consolidate compiler generated dependencies of target czmq_objects
[ 80%] Built target czmq_objects
[ 82%] Built target czmq
[ 84%] Built target czmq-static
Consolidate compiler generated dependencies of target zmakecert
[ 88%] Built target zmakecert
Consolidate compiler generated dependencies of target zsp
[ 92%] Built target zsp
Consolidate compiler generated dependencies of target test_randof
[ 96%] Built target test_randof
Consolidate compiler generated dependencies of target czmq_selftest
[100%] Built target czmq_selftest
[100%] Built target copy-selftest-ro
[100%] Built target make-selftest-rw
Install the project...
-- Install configuration: "Debug"
-- Installing: /usr/local/include/czmq_library.h
-- Installing: /usr/local/include/czmq_prelude.h
-- Installing: /usr/local/include/czmq.h
-- Installing: /usr/local/include/zactor.h
-- Installing: /usr/local/include/zarmour.h
-- Installing: /usr/local/include/zcert.h
-- Installing: /usr/local/include/zcertstore.h
-- Installing: /usr/local/include/zchunk.h
-- Installing: /usr/local/include/zclock.h
-- Installing: /usr/local/include/zconfig.h
-- Installing: /usr/local/include/zdigest.h
-- Installing: /usr/local/include/zdir.h
-- Installing: /usr/local/include/zdir_patch.h
-- Installing: /usr/local/include/zfile.h
-- Installing: /usr/local/include/zframe.h
-- Installing: /usr/local/include/zhash.h
-- Installing: /usr/local/include/zhashx.h
-- Installing: /usr/local/include/ziflist.h
-- Installing: /usr/local/include/zlist.h
-- Installing: /usr/local/include/zlistx.h
-- Installing: /usr/local/include/zloop.h
-- Installing: /usr/local/include/zmsg.h
-- Installing: /usr/local/include/zpoller.h
-- Installing: /usr/local/include/zsock.h
-- Installing: /usr/local/include/zstr.h
-- Installing: /usr/local/include/zsys.h
-- Installing: /usr/local/include/zuuid.h
-- Installing: /usr/local/include/zauth.h
-- Installing: /usr/local/include/zbeacon.h
-- Installing: /usr/local/include/zgossip.h
-- Installing: /usr/local/include/zmonitor.h
-- Installing: /usr/local/include/zproxy.h
-- Installing: /usr/local/include/zrex.h
-- Installing: /usr/local/include/zgossip_msg.h
-- Installing: /usr/local/include/zsock_option.inc
-- Installing: /usr/local/include/zgossip_engine.inc
-- Installing: /usr/local/include/zhash_primes.inc
-- Installing: /usr/local/include/sha1.inc_c
-- Installing: /usr/local/include/sha1.h
-- Installing: /usr/local/include/slre.inc_c
-- Installing: /usr/local/include/slre.h
-- Installing: /usr/local/include/readme.txt
-- Installing: /usr/local/include/zargs.h
-- Installing: /usr/local/include/zproc.h
-- Installing: /usr/local/include/ztimerset.h
-- Installing: /usr/local/include/ztrie.h
-- Installing: /usr/local/include/zhttp_client.h
-- Installing: /usr/local/include/zhttp_server.h
-- Installing: /usr/local/include/zhttp_server_options.h
-- Installing: /usr/local/include/zhttp_request.h
-- Installing: /usr/local/include/zhttp_response.h
-- Installing: /usr/local/include/zosc.h
-- Installing: /usr/local/lib/libczmq.so.4.2.1
-- Installing: /usr/local/lib/libczmq.so.4
-- Set runtime path of "/usr/local/lib/libczmq.so.4.2.1" to ""
-- Installing: /usr/local/lib/libczmq.so
-- Installing: /usr/local/lib/libczmq.a
-- Installing: /usr/local/lib/pkgconfig/libczmq.pc
-- Installing: /usr/local/share/cmake/czmq/czmqTargets.cmake
-- Installing: /usr/local/share/cmake/czmq/czmqTargets-debug.cmake
-- Installing: /usr/local/share/cmake/czmq/czmqConfig.cmake
-- Installing: /usr/local/share/cmake/czmq/czmqConfigVersion.cmake
-- Installing: /usr/local/bin/zmakecert
-- Set runtime path of "/usr/local/bin/zmakecert" to ""

# 查看安装
$ ls -la /usr/local/lib | grep -Ein "czmq"
8:-rw-r--r-- 1 admin administrators 2068196 Jul 10 18:09 libczmq.a
9:lrwxrwxrwx 1 admin administrators      12 Jul 10 18:10 libczmq.so -> libczmq.so.4*
10:lrwxrwxrwx 1 admin administrators      16 Jul 10 18:10 libczmq.so.4 -> libczmq.so.4.2.1*
11:-rwxr-xr-x 1 admin administrators 1235376 Jul 10 18:09 libczmq.so.4.2.1*
```



### 2.10.01 libzmq-dev

libczmq-dev的依赖库，同样在NI LINUX RT本身没有，并且opkg也没有，只能自己去下载编译安装

下载地址（同样选择下载release版本4.3.5）

```http
https://github.com/zeromq/libzmq
```

编译安装

```bash
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/zeromq-4.3.5

$ mkdir build

$ cd build

$ cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Detected ZMQ Version - 4.3.5
........（省略）...........
CMake Deprecation Warning at tests/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Warning (dev) at tests/CMakeLists.txt:342 (message):
  Test 'test_bind_stream_fuzzer' is not known to CTest.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at tests/CMakeLists.txt:342 (message):
  Test 'test_bind_ws_fuzzer' is not known to CTest.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at tests/CMakeLists.txt:342 (message):
  Test 'test_connect_stream_fuzzer' is not known to CTest.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at tests/CMakeLists.txt:342 (message):
  Test 'test_connect_ws_fuzzer' is not known to CTest.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at tests/CMakeLists.txt:342 (message):
  Test 'test_socket_options_fuzzer' is not known to CTest.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Deprecation Warning at unittests/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 2.8.12 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Configuring done
-- Generating done
-- Build files have been written to: /home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/zeromq-4.3.5/build


make
[  1%] Building C object CMakeFiles/objects.dir/external/sha1/sha1.c.o
[  1%] Building CXX object CMakeFiles/objects.dir/src/precompiled.cpp.o
[  1%] Building CXX object CMakeFiles/objects.dir/src/address.cpp.o
[  2%] Building CXX object CMakeFiles/objects.dir/src/channel.cpp.o
[  2%] Building CXX object CMakeFiles/objects.dir/src/client.cpp.o
[  2%] Building CXX object CMakeFiles/objects.dir/src/clock.cpp.o
[  2%] Building CXX object CMakeFiles/objects.dir/src/ctx.cpp.o
[  3%] Building CXX object CMakeFiles/objects.dir/src/curve_mechanism
........（省略）...........
[ 96%] Built target unittest_ypipe
[ 96%] Building CXX object unittests/CMakeFiles/unittest_poller.dir/unittest_poller.cpp.o
[ 96%] Linking CXX executable ../bin/unittest_poller
[ 96%] Built target unittest_poller
[ 96%] Building CXX object unittests/CMakeFiles/unittest_mtrie.dir/unittest_mtrie.cpp.o
[ 97%] Linking CXX executable ../bin/unittest_mtrie
[ 97%] Built target unittest_mtrie
[ 97%] Building CXX object unittests/CMakeFiles/unittest_ip_resolver.dir/unittest_ip_resolver.cpp.o
[ 97%] Linking CXX executable ../bin/unittest_ip_resolver
[ 97%] Built target unittest_ip_resolver
[ 97%] Building CXX object unittests/CMakeFiles/unittest_udp_address.dir/unittest_udp_address.cpp.o
[ 97%] Linking CXX executable ../bin/unittest_udp_address
[ 97%] Built target unittest_udp_address
[ 98%] Building CXX object unittests/CMakeFiles/unittest_radix_tree.dir/unittest_radix_tree.cpp.o
[ 98%] Linking CXX executable ../bin/unittest_radix_tree
[ 98%] Built target unittest_radix_tree
[ 98%] Building CXX object unittests/CMakeFiles/unittest_curve_encoding.dir/unittest_curve_encoding.cpp.o
[100%] Linking CXX executable ../bin/unittest_curve_encoding
[100%] Built target unittest_curve_encoding

$ sudo make install
Consolidate compiler generated dependencies of target objects
[ 30%] Built target objects
[ 30%] Built target libzmq
[ 30%] Built target libzmq-static
Consolidate compiler generated dependencies of target local_lat
[ 31%] Built target local_lat
Consolidate compiler generated dependencies of target remote_lat
[ 32%] Built target remote_lat
Consolidate compiler generated dependencies of target local_thr
........（省略）...........
[ 97%] Built target unittest_mtrie
Consolidate compiler generated dependencies of target unittest_ip_resolver
[ 97%] Built target unittest_ip_resolver
Consolidate compiler generated dependencies of target unittest_udp_address
[ 97%] Built target unittest_udp_address
Consolidate compiler generated dependencies of target unittest_radix_tree
[ 98%] Built target unittest_radix_tree
Consolidate compiler generated dependencies of target unittest_curve_encoding
[100%] Built target unittest_curve_encoding
Install the project...
-- Install configuration: "Release"
-- Installing: /usr/local/lib64/pkgconfig/libzmq.pc
-- Installing: /usr/local/bin/local_lat
-- Set runtime path of "/usr/local/bin/local_lat" to ""
-- Installing: /usr/local/bin/remote_lat
-- Set runtime path of "/usr/local/bin/remote_lat" to ""
-- Installing: /usr/local/bin/local_thr
-- Set runtime path of "/usr/local/bin/local_thr" to ""
-- Installing: /usr/local/bin/remote_thr
-- Set runtime path of "/usr/local/bin/remote_thr" to ""
-- Installing: /usr/local/bin/inproc_lat
-- Set runtime path of "/usr/local/bin/inproc_lat" to ""
-- Installing: /usr/local/bin/inproc_thr
-- Set runtime path of "/usr/local/bin/inproc_thr" to ""
-- Installing: /usr/local/bin/proxy_thr
-- Set runtime path of "/usr/local/bin/proxy_thr" to ""
-- Installing: /usr/local/lib64/libzmq.so.5.2.5
-- Installing: /usr/local/lib64/libzmq.so.5
-- Installing: /usr/local/lib64/libzmq.so
-- Installing: /usr/local/include/zmq.h
-- Installing: /usr/local/include/zmq_utils.h
-- Installing: /usr/local/lib64/libzmq.a
-- Up-to-date: /usr/local/include/zmq.h
-- Up-to-date: /usr/local/include/zmq_utils.h
-- Installing: /usr/local/share/zmq/AUTHORS.txt
-- Installing: /usr/local/share/zmq/LICENSE.txt
-- Installing: /usr/local/share/zmq/NEWS.txt
-- Installing: /usr/local/lib64/cmake/ZeroMQ/ZeroMQTargets.cmake
-- Installing: /usr/local/lib64/cmake/ZeroMQ/ZeroMQTargets-release.cmake
-- Installing: /usr/local/lib64/cmake/ZeroMQ/ZeroMQConfig.cmake
-- Installing: /usr/local/lib64/cmake/ZeroMQ/ZeroMQConfigVersion.cmake

# 查看安装
$ ls -la /usr/local/lib64 | grep -Ein "zmq"
8:-rw-r--r-- 1 admin administrators 2077324 Jul 10 18:04 libzmq.a
9:lrwxrwxrwx 1 admin administrators      11 Jul 10 18:06 libzmq.so -> libzmq.so.5*
10:lrwxrwxrwx 1 admin administrators      15 Jul 10 18:06 libzmq.so.5 -> libzmq.so.5.2.5*
11:-rwxr-xr-x 1 admin administrators 1087160 Jul 10 18:04 libzmq.so.5.2.5*
```





## 2.11 uuid-dev

uuid-dev 是一个用于开发的软件包，它提供了在 Linux 系统上生成和操作 UUID（Universally Unique Identifier，通用唯一标识符）的开发库和工具。UUID 是一种标准化的格式，用于唯一地标识信息，通常以 32 个十六进制数字表示，例如 550e8400-e29b-41d4-a716-446655440000

查找库已经有了，暂时不安装了

```bash
$ ls /usr/lib | grep -Ein "uuid"
565:libuuid.so@
566:libuuid.so.1@
567:libuuid.so.1.3.0*
```





## 2.12 default-jdk

默认JDK

由于opkg下并没有直接可以使用的JDK，并且NI LINUX RT系统默认也没有JDK，因此需要手动安装

下载地址

```http
https://www.oracle.com/cn/java/technologies/downloads/#java17
```

我的系统是X86架构的，并且包管理器是opkg所以选择了

| x64 Compressed Archive | 174.29 MB | https://download.oracle.com/java/17/latest/jdk-17_linux-x64_bin.tar.gz ( [sha256](https://download.oracle.com/java/17/latest/jdk-17_linux-x64_bin.tar.gz.sha256)) |
| ---------------------- | --------- | ------------------------------------------------------------ |
|                        |           |                                                              |

解压后在bin目录可以正常查看到jdk版本

```bash
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/jdk-17.0.11/bin

$ ./java -version
java version "17.0.11" 2024-04-16 LTS
Java(TM) SE Runtime Environment (build 17.0.11+7-LTS-207)
Java HotSpot(TM) 64-Bit Server VM (build 17.0.11+7-LTS-207, mixed mode, sharing)
```

设置JDK的环境变量

```bash
# 打开环境变量设置文件
sudo vim ~/.bashrc

# 添加环境变量
export JAVA_HOME=/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/jdk-17.0.11
export PATH=$JAVA_HOME/bin:$PATH

# 生效
source ~/.bashrc

# 测试，切换成任意目录都可以找到了
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref
$ java -version
java version "17.0.11" 2024-04-16 LTS
Java(TM) SE Runtime Environment (build 17.0.11+7-LTS-207)
Java HotSpot(TM) 64-Bit Server VM (build 17.0.11+7-LTS-207, mixed mode, sharing)
```





## 2.13 build-essential

`build-essential` 是一个在基于 Debian 的 Linux 发行版中常见的软件包，它提供了构建软件包源代码的基本工具集合。它的主要作用是为开发者和系统管理员提供一组必要的工具，使他们能够编译和安装软件包，特别是那些需要从源代码构建的软件包。

在NI LINUX RT下暂时无法安装（opkg不存在并且也无法安装deb），属于ubuntu专属





## 2.14 libcurl4-openssl-dev

`libcurl4-openssl-dev` 是针对 libcurl 库的开发包，它允许开发者在其应用程序中使用 libcurl 提供的功能。以下是它的主要组成部分和作用：

1. **libcurl**: `libcurl` 是一个开源的客户端 URL 传输库，支持多种协议，包括 HTTP、HTTPS、FTP 等。它允许应用程序通过简单的接口来进行网络通信和数据传输。
2. **libcurl4-openssl**: 这个包使用 OpenSSL 库作为 libcurl 的加密后端。OpenSSL 是一个流行的加密库，支持 SSL/TLS 协议，用于安全地进行网络通信。

查询下来只有deb版本的库，并且OPKG也无法直接安装该库，所以分别安装`libcurl4`和`openssl`



### 2.14.01 libcurl4

查看NI LINUX RT下是否已存在

```bash
# 库文件存在
$ ls -la /usr/lib | grep -Ein "curl"
163:lrwxrwxrwx  1 admin administrators       16 Mar  9  2018 libcurl.so -> libcurl.so.4.7.0*
164:lrwxrwxrwx  1 admin administrators       16 Mar  9  2018 libcurl.so.4 -> libcurl.so.4.7.0*
165:-rwxr-xr-x  1 admin administrators   504024 Mar  9  2018 libcurl.so.4.7.0*

# 头文件存在
$ ls -la /usr/include | grep -Ein "curl"
38:drwxr-xr-x  2 admin administrators   4096 Mar  9  2018 curl/
```

下载地址

```http
https://pkgs.org/download/libcurl4
```





### 2.14.02 openssl

查看NI LINUX RT下是否已存在

```bash
# 库文件存在
$ ls -la /usr/lib | grep -Ein "openssl"
285:lrwxrwxrwx  1 admin administrators       27 Mar  9  2018 libgnutls-openssl.so -> libgnutls-openssl.so.27.0.2*
286:lrwxrwxrwx  1 admin administrators       27 Mar  9  2018 libgnutls-openssl.so.27 -> libgnutls-openssl.so.27.0.2*
287:-rwxr-xr-x  1 admin administrators    97024 Mar  9  2018 libgnutls-openssl.so.27.0.2*

# 头文件存在
$ ls -la /usr/include | grep -Ein "openssl"
177:drwxr-xr-x  2 admin administrators   4096 Mar  9  2018 openssl/
```





# 三、GRPC迁移







# 

# 问题记录



## Cmake找到g++



问题描述：在libcpputest-dev项目的cmake ..时报错如下

```bash
cmake ..
-- The CXX compiler identification is unknown
CMake Error at CMakeLists.txt:1 (project):
  No CMAKE_CXX_COMPILER could be found.

  Tell CMake where to find the compiler by setting either the environment
  variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path
  to the compiler, or to the compiler name if it is in the PATH.
```

问题原因：NI LINUX RT下g++没有直接添加链接

```bash
$ gcc --version
gcc (GCC) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ g++ --version
-bash: g++: command not found
```

问题解决：

```bash
# 查找gcc所在位置
$ which gcc
/usr/bin/gcc

# 安装了以后查找还是没有，似乎没什么用
$ sudo opkg install g++
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/main/core2-64/libatomic1_11.4.0-r0.10_core2-64.ipk.
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/main/core2-64/libatomic-dev_11.4.0-r0.10_core2-64.ipk.
Downloading http://download.ni.com/ni-linux-rt/feeds/2024Q1/x64/main/core2-64/g++_11.4.0-r0.10_core2-64.ipk.
Installing libatomic1 (11.4.0) on root
Installing libatomic-dev (11.4.0) on root
Installing g++ (11.4.0) on root
Configuring libatomic1.
Configuring libatomic-dev.
Configuring g++.
$ which g++

# 查看gcc的链接
$ ls -la /usr/bin | grep -Ein "gcc"
47:lrwxrwxrwx   1 admin administrators        3 Mar  9  2018 cc -> gcc*
199:lrwxrwxrwx   1 admin administrators       22 Mar  9  2018 gcc -> x86_64-nilrt-linux-gcc*
732:-rwxr-xr-x   1 admin administrators  1325760 Mar  9  2018 x86_64-nilrt-linux-gcc*
733:-rwxr-xr-x   1 admin administrators    35296 Mar  9  2018 x86_64-nilrt-linux-gcc-ar*
734:-rwxr-xr-x   1 admin administrators    35296 Mar  9  2018 x86_64-nilrt-linux-gcc-nm*
735:-rwxr-xr-x   1 admin administrators    35296 Mar  9  2018 x86_64-nilrt-linux-gcc-ranlib*

# 查找g++
# 在NI LINUX RT下这个指令查出来的结果有很多并不包含g++的结果，但可以看到g++是x86_64-nilrt-linux-g++
ls -la /usr/bin | grep -Ein "g++"

# 查看版本
$ x86_64-nilrt-linux-g++ --version
x86_64-nilrt-linux-g++ (GCC) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# 创建g++的软连接
$ ln -s x86_64-nilrt-linux-g++ g++

# 查看结果
$ ls -la | grep "g++"
lrwxrwxrwx   1 admin administrators       22 Jan  1 00:34 g++ -> x86_64-nilrt-linux-g++*
-rwxr-xr-x   1 admin administrators  1329856 May 29  2023 x86_64-nilrt-linux-g++*

# 设置环境变量
$ sudo ~/.bashrc
# 在末尾添加
export PATH=$PATH:/usr/lib
# 生效
source ~/.bashrc

# 在任意目录测试
$ pwd
/home/admin/git_pro/acephere_runtime/thirdParty/celix_ref/cpputest-3.8/build
$ g++ --version
g++ (GCC) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```





























