# CMake generated Testfile for 
# Source directory: /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test
# Build directory: /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/test
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(Empty "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/1.plist")
ADD_TEST(Small "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/2.plist")
ADD_TEST(Medium "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/3.plist")
ADD_TEST(Large "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/4.plist")
ADD_TEST(Huge "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/5.plist")
ADD_TEST(Big_Array "plist_test" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/6.plist")
ADD_TEST(EmptyCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/1.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/1.plist.out")
ADD_TEST(SmallCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/2.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/2.plist.out")
ADD_TEST(MediumCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/3.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/3.plist.out")
ADD_TEST(LargeCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/4.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/4.plist.out")
ADD_TEST(HugeCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/5.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/5.plist.out")
ADD_TEST(Big_ArrayCmp "plist_cmp" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/6.plist" "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test/data/6.plist.out")
