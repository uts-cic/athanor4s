# Overview

This repository is setup to provide an interface between athanor-server and
and the athanor-core cpp code. It uses the sbt-jni interface to generate 
the Java native interface header files and to compile the cpp interface 
program. The cpp interface parts is linked with the athanor-core cpp 
objects that are produced by the athanor project and are copied to this 
project. These are deemed stable enough not to require frequent source 
code modification and recompiles. 

See [sbt jni interface](https://index.scala-lang.org/jodersky/sbt-jni/jni-library/0.4.4?target=_2.11)
for a description of  the sbt Java native interface 

Refer to [Bintray for plugins - sbt reference manual](http://www.scala-sbt.org/0.13/docs/Bintray-For-Plugins.html) 
for a discussion of publishing to binTray. 

See [nlytx nlp-project](https://github.com/nlytx/nlytx-nlp/blob/master/build.sbt) for an example 
of how to publish to binTray 
 
# Project Organisation 

The project is split into directories core and native 
following the [one project example](https://github.com/jodersky/sbt-jni/tree/master/plugin/src/sbt-test/sbt-jni/oneproject). 

The JNI project recommends two projects one for core and native components. Such setup however results in two jars that need to be 
published, and probably requires more changes to the DynLoader program that was ported from the athanor project, and is 
written to extract the dll from the one jar that was built by athanor. 

The core part of the project consists of only two scala files which were ported from two similar files in 
the athanor repository: 

- JAtanor.scala : This contains the scala native interface
- DynLoaderFromJar.scala: This program extracts the dll from the jar. It is probably only needed so that it 
can extract and load the appropriate dll for the given operating system. This saves the user having to download
the appropriate dll for their platform and pointing the scala code at it.
Note that this program is written in a java style, and requires further modifications and improvements as 
more operating systems are tests (It was only tested for Linux with this new set-up).
   
The native part of the project consists of the following parts: 

athanor.cxx: This implements the JAtanor.scala interface and is designed to link to the athanor-core objects.
CMakeLists.txt: This contains the build rules for the CMake Utility which is used by the sbt-jni interface
to compile and link the cpp parts. These rules are designed to be adaptable for multiple operating systems.
The CMake Utility is more portable than the Make utility that is used in the athanor repository.  

The include directory contains the generated header file (from the native compile), as well as few header 
files that are copied/duplicated from the athanor repository and are the minimum necessary to compile the 
athanor.cxx part.
 
# Native compile (sbt nativeCompile) 

Since this project does not duplicate the athanor cpp parts, we have to somehow be able to link to them. 
The method that is used is to place an archive of the objects for each operating system in an operating
system specific directory. For example, for the Linux system, the athanor-core archive is placed in: 
native/objs/Linux/athanor-core.a 

The athanor-core.a file can be produced by adding the following rule to the athanor repository Makefile: 

        libatanor_archive: 
            ar crf $(BINPATH)/libatanor.a $(OBJECTATANOR)


The CMake Utility is used by JNI to produce the cpp dll that is placed inside the target jar. The cpp dll 
links the athanor.cxx to the athanor-core archive library to produce a dll that can be placed inside the
athanor4s interface jar (following the issuing of an sbt package command). 

We use an archive library rather than the libatanor dll that athanor core currently produces, since it 
is not feasible to link an object with a dll to produce a new DLL (The CMake utility does not seem to 
support this). Of course, we could copy the entire athanor source code and recompile all the parts 
each time, but this approach was not adopted in order to keep the athanor4s interface code separate, 
and given that athanor core project parts are stable enough not to require frequent recompilation.

# Interfacing the different parts 

The athanor server code would look for the athanor4s jar in its lib directory. It invokes the JAtanor 
scala part. The JAtanor constructor invokes the DynLoader program which knows the name and the offset 
of the cpp dll in the jar. For example, for the Linux operating system, DynLoader looks to find the 
libathanor.so dll in the native/x86_64-linux/ path. This has to match what was produced by the 
cmake utility and the sbt package commands. The athanor.cxx implementation code is then invoked 
and since it is linked with the rest of the cpp athanor code, it can find that code without the 
need for any dll search, or any additional environmental setup.
 
 
# Native Header file generation

Invoking sbt javah generates the following header file from the sbt JAtanor.scala interface 
code:
 
  com_xerox_jatanor_JAtanor.h

This is included by the athanor.cxx implementation code, which implements this interface. 



  

