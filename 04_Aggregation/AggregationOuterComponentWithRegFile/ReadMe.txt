Notes For Developer .....
-------------------------
1) Inner Component Developer Will Give 2 Files, One The DLL & The Other
   Is H File.

2) Outer Component Developer Will Use Inner Component's H File In Its
   Code.
3) Outer Component Developer Will Also Have Its Own DLL & H Files.

4) During Deployment He Will Deploy Both DLLs But Not Both H Files.

5) Instead While Deploying To The Client, He Will Create Such A H File 
   Which Will Encarporate Information Of Both Inner & Outer Components 
   Headers Into A Seperate H File And Will Deploy This Seperate H File.
   This Seperate H File Will Contain....

   - Interface Definitions Of Both Inner & Outer Components.
   - CLSID Of Outer Component Only.
   - IID's Of All Interfaces Of Both Inner & Outer Components.

   So, If We Assume That Inner Component Is Developed By Some Other
   Vendor, The Outer Component Developer Will Behave Like That He
   Himself Developed Inner Component Too By Hiding All Information
   Of Inner Component From The Client ( i.e. CLSID Of Inner Component )

   *** SPECIAL NOTE : This Seperate .H File ( Which Is To Be Deployed 
                      To The Client ) Is Just For Deployment And Hence
                      Must Not Be Included In The Project Of Outer
                      Component Server, Though It Is Present In Its
                      Project Directory.

6) Then He Will Craete A REG File And Will Also Deploys It. This REG 
   File Will Register CLSIDs & DLLs Of Both Inner & Outer Components.

7) So In All There Will Be 4 Files.....

   a) Outer Component's DLL
   b) Inner Component's DLL
   c) Special Header File ( Inner + Outer Component's H Files )
   d) REG File
