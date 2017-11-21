# athanor4s

This is the athanor-server to athanor scala project interface 

To built this project: 

   1. sbt nativeCompile

   This will build the cpp dll. Repeat this for each platform that you wish to include 
   (Currently Linux is the only tested platform). 

   2. sbt package 
   
   This produces the following jar
   
       target/sbt-0.13/athanor4s-0.1.0.jar

        ~/athanor4s$ jar tvf target/sbt-0.13/athanor4s-0.1.0.jar   252 Mon Nov 20 15:17:12 AWST 2017 META-INF/MANIFEST.MF
        0 Mon Nov 20 15:17:12 AWST 2017 com/
        0 Mon Nov 20 15:17:12 AWST 2017 com/xerox/
        0 Mon Nov 20 15:17:12 AWST 2017 com/xerox/jatanor/
        0 Mon Nov 20 15:17:12 AWST 2017 native/
        0 Mon Nov 20 15:17:12 AWST 2017 native/x86_64-linux/
        19787 Mon Nov 20 14:55:48 AWST 2017 com/xerox/jatanor/DynLoaderFromJar.class
        16997616 Mon Nov 20 15:17:12 AWST 2017 native/x86_64-linux/libathanor.so
        2953 Mon Nov 20 14:55:48 AWST 2017 com/xerox/jatanor/JAtanor.class

   3. sbt publish

   This will publish the jar to bintray so it is ready to be download by the athanor-server project 
    
  
