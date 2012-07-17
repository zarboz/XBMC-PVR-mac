ifeq ("10.7", "10.4")
  ifeq ("i386", "ppc")
    host_alias=powerpc-apple-darwin8
  else
    host_alias=i386-apple-darwin8
  endif
  platform_gnu=gnu89
  platform_cc=gcc-4.0
  platform_cpp=cpp-4.0
  platform_cxx=g++-4.0
  platform_gcc_version=4.0
  platform_sdk_version=10.7u
  export MACOSX_DEPLOYMENT_TARGET=10.4
  platform_min_version=macosx-version-min=10.4
else 
  xcode3_chk=case 4.3.3 in 3.*.*) echo 1 ;; *) echo 0 ;; esac
  ifeq ($(shell $(xcode3_chk)) , 1)
    platform_cc=gcc-4.2
    platform_cpp=cpp-4.2
    platform_cxx=g++-4.2
  else
    platform_cc=llvm-gcc-4.2
    platform_cpp=llvm-gcc-4.2 -E
    platform_cxx=llvm-g++-4.2
  endif
  platform_gnu=gnu99
  platform_gcc_version=4.2
  platform_sdk_version=10.7
  host_alias=i386-apple-darwin
  export MACOSX_DEPLOYMENT_TARGET=10.6
  platform_min_version=macosx-version-min=10.6
endif

platform_path=/Applications/Xcode.app/Contents/Developer
platform_os_cflags=-arch i386 -no_compact_linkedit
platform_os_ldflags=-arch i386 -no_compact_linkedit
platform_sdk_path=/Volumes/The

export NM=${platform_path}/usr/bin/nm
export CPP=${platform_path}/usr/bin/${platform_cpp}
export CXXCPP=${CPP}
export CPPFLAGS+=-no-cpp-precomp -I${PREFIX}/include -m${platform_min_version} -isysroot ${platform_sdk_path} ${platform_os_cflags}
export CC=/usr/bin/${platform_cc}
export CFLAGS+=-std=${platform_gnu} -no-cpp-precomp -m${platform_min_version} -isysroot ${platform_sdk_path} ${platform_os_cflags}
export LD=${platform_path}/usr/bin/ld
export LDFLAGS+=-m${platform_min_version} -isysroot ${platform_sdk_path} ${platform_os_ldflags} -L${PREFIX}/lib
export CXX=/usr/bin/${platform_cxx}
export CXXFLAGS+=-m${platform_min_version} -isysroot ${platform_sdk_path} ${platform_os_cflags}
export AR=${platform_path}/usr/bin/ar
export AS=${platform_path}/usr/bin/as
export M4=/Users/Shared/xbmc-depends/toolchain/bin/m4
export STRIP=${platform_path}/usr/bin/strip
export RANLIB=${platform_path}/usr/bin/ranlib
export ACLOCAL=/Users/Shared/xbmc-depends/toolchain/bin/aclocal -I ${PREFIX}/share/aclocal -I /Users/Shared/xbmc-depends/toolchain/share/aclocal
export LIBTOOL=/Users/Shared/xbmc-depends/toolchain/bin/glibtool
export LIBTOOLIZE=/Users/Shared/xbmc-depends/toolchain/bin/glibtoolize
export PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig:${platform_sdk_path}/usr/lib/pkgconfig
export PATH:=/Users/Shared/xbmc-depends/toolchain/bin:${PREFIX}/bin:${platform_path}/usr/bin:/Developer/usr/bin:${PATH}
