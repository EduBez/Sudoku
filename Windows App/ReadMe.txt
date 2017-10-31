Hello,

When doing this assignment I opted to use C++Builder from Embarcadero, a company formerly known as Borland.

I made that decision because I wanted to develop the solution and show the results in a Windows GUI application.

I could have used Visual Studio 2017 for this project, but the only native Windows 32 GUI framework
that Visual Studio 2017 still offers is the Microsoft Foundation Classes (MFC) that dates back to 1992.

The other option I had was to use Windows Forms, but that would require writing the code in C# or in C++/CLI, or
mixing C# (on the user interface side) with C++. For me that was not an option.

The project was completely written in C++14, using the CLang compiler that comes with C++Builder, and it makes use of
the Visual Component Library (VCL) to create the native Windows GUI.

To be able to build the project you will need a free copy of Embarcadero RAD Studio.

You can download a free trial of Embarcadero Studio at the link:
https://www.embarcadero.com/products/rad-studio/start-for-free

If you don't want to go through the registration process to download the free trial of the product I have already
created an account at Embarcadero just for this assignment:

Product: RAD Studio 10.2.1 Tokyo Architect Trial 
Serial Number(s): JSFK-PV6Y44-4ZNGDK-HJNS 

Login Name: Qlik.Dev.Assignment@gmail.com
Password: Abcd12345 

First Name: Eduardo 
Last Name: Bezerra 

You can download the Embarcadero RAD Studio installer directly from this link:
http://altd.embarcadero.com/download/radstudio/10.2/radstudio10_2_1_esd.exe

Please feel free to use those credentials to install the trial because they were never used before.
This will easy the trouble of registering with Embarcadero and speed up the code review process.

When installing Embarcadero RAD Studio you must choose:

1 - Check "I have signed up for a trial at embarcadero.com" option
2 - Enter the Serial Number above or the one you received from the free trial email
3 - Click the Register button
4 - Next you will see the "RAD Studio Platform Selection" form
5 - You can leave the defaults and uncheck all IOS options
6 - If you want to compile the code for 64 bit you must check "C++Builder Windows 64-bit Enterprise Trial"
7 - Just click INSTALL and you're done


One final note: the project is dependent on the open source Boost Libraries.

You can install the Boost Libraries directly from inside the Embarcadero RAD Studio IDE.
Click on the menu Tools / GetIt Package Manager and then search for Boost.
The Boost Libraries package will appear, just click on it to install.

I hope my choice is still aligned with the requisites of this assignment.

My best regards,
Eduardo
