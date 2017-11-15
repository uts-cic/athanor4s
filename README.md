# athanor4s

This is the athanor-server to athanor scala project interface 

To built this project: 

   1. Place the libjatanor.so dll for the linux plaform that is produced by athanor under src/main/resources/linux
      (Retrieving this dll will be automated later  on).
   3. In the project home directory - type: sbt package

This will produce: 
    target/scala-2.12/athanor-interface_2.12-1.0.jar 
    
which you can link to from the athanor-server lib directory and test.
     ln -s HOME_DIR/athanor4s/target/scala-2.12/athanor-interface_2.12-1.0-SNAPSHOT.jar athanor.jar


The contents of this dll would look like: 

    jar tvf target/scala-2.12/athanor-interface_2.12-1.0-SNAPSHOT.jar 
   
   279 Wed Nov 15 12:03:58 AWST 2017 META-INF/MANIFEST.MF
     0 Wed Nov 15 12:03:58 AWST 2017 com/
     0 Wed Nov 15 12:03:58 AWST 2017 com/xerox/
     0 Wed Nov 15 12:03:58 AWST 2017 com/xerox/jatanor/
     0 Wed Nov 15 12:03:58 AWST 2017 linux/
16997688 Tue Nov 14 15:55:04 AWST 2017 linux/libjatanor.so
  7096 Wed Nov 15 10:49:24 AWST 2017 com/xerox/jatanor/DynLoaderFromJar.class
   890 Wed Nov 15 10:49:24 AWST 2017 com/xerox/jatanor/JAtanor.class
