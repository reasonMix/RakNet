#!/usr/bin/env bash
rm -rf publish
mkdir -p publish/osx
mkdir -p publish/ios
mkdir -p publish/android

polly --reconfig --install --config RelWithDebInfo --toolchain osx-10-12-dep-10-10
mv ./Lib/RakNetLibStatic/libRakNetLibStatic.a ./publish/osx/libRakNetLibStatic.a

polly --reconfig --install --config RelWithDebInfo --toolchain ios-10-1 --ios-multiarch --ios-combined
mv ./Lib/RakNetLibStatic/libRakNetLibStatic.a ./publish/ios/libRakNetLibStatic.a

polly --reconfig --install --config RelWithDebInfo --toolchain android-ndk-r10e-api-19-armeabi-v7a
mv ./Lib/RakNetLibStatic/libRakNetLibStatic.a ./publish/android/libRakNetLibStatic.a

cp ./publish/osx/libRakNetLibStatic.a /Volumes/LenvnoDisk/TribalWars/frameworks/runtime-src/Classes/deps/osx/lib/libraknet.a
cp ./publish/ios/libRakNetLibStatic.a /Volumes/LenvnoDisk/TribalWars/frameworks/runtime-src/Classes/deps/ios/lib/libraknet.a
cp ./publish/android/libRakNetLibStatic.a /Volumes/LenvnoDisk/TribalWars/frameworks/runtime-src/Classes/deps/android/armeabi-v7a/libraknet.a
