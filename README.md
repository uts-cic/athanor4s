# athanor4s

This is the athanor-server to athanor scala project interface 

It is currently in transition as it is being set-up and 
gradually transofrmed into an sbt project. 


To built this project: 

   1. Place the libjatanor.so dll for the linux plaform that is produced by athanor under src/main/resources/linux
      (Retrieving this dll will be automated later  on).
   3. In the project home directory - type: ant compile

This will produce: 
    target/java/dist/jatanor.jar

which you can link to from the athanor-server lib directory and test. 

The contents of this dll would look like: 

    jar tvf java/dist/jatanor.jar 

     0 Tue Nov 14 15:53:44 AWST 2017 META-INF/
     211 Tue Nov 14 15:53:42 AWST 2017 META-INF/MANIFEST.MF
     0 Tue Nov 14 11:12:18 AWST 2017 com/
     0 Tue Nov 14 11:12:18 AWST 2017 com/xerox/
     0 Tue Nov 14 11:12:18 AWST 2017 com/xerox/jatanor/
     6349 Tue Nov 14 15:53:44 AWST 2017 com/xerox/jatanor/DynLoaderFromJar.class
     780 Tue Nov 14 15:53:44 AWST 2017 com/xerox/jatanor/JAtanor.class
     0 Tue Nov 14 13:56:38 AWST 2017 linux/
     16997688 Tue Nov 14 13:56:38 AWST 2017 linux/libjatanor.so


