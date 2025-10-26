# EVNT
## Introduction
This project is an Event and Party Planning application. It was created to fill a growing need, as the popular opinion of other platforms such as Facebook and Twitter are in decline and people are in need of an app to facilitate the easy coordination of events. Our app titled EVNT allows users to login to their individual accounts and then create events which are accessible to other users via our database. Our users can search and browse other users' events to find events uploaded to the site. The user can view their own as well as other users' profiles. Furthermore they can search for specific users and follow (or unfollow) them. They can edit their personal information and view details about events they create. 

While we originally intended for much more functionality for our app, we decided to scale the design back to better suit what was feasible for us to create with a good standard of quaity. This meant the removal of 3 features we had intended, the Map system (To visually display events in your area for easy browsing), the private and public typing of parties (To allow only certain users access to specific events), and finally the automated deletion of events (after their set end time has passed). Despite not being able to add these features (cut back for time), we still planned our app and designed it in a way that these features would be easily extensible if we had more time. 

The most important feature which we needed to cut close to the end was the invites system, because of this we've left in several sections of code and the UML sections for it. This system would've used the database and we had created as well as handlers and several functions. We have left those sections in despite their non-operational nature for potential extensibility and expandability in the future and to show the progress we had towards those sections of our inital plans and user stories. 

Our final product represents over a month of work and collaboration and we hope you appricate the effort and ideas that we have put into it. 

Thanks,


## Installation and Running Notes
1. On a Linux system (our system was created on Linux Ubuntu 22.04.2), install the following 6 libraries with the following commands:
    - `sudo apt install cmake`
    - `sudo apt install libgtk-3-dev`
    - `sudo apt install git`
    - `sudo apt install libwxbase3.0-dev`
    - `sudo apt install libwxgtk3.0-gtk3-dev`
    - `sudo apt install curl`
2. Download the zip file found on OWL and unzip it
3. Go into the `group10` folder and `unzip wxWidgets-3.2.2.1.tar.bz2`
4. Go into the terminal and `cd` into `group10`
5. `cd` into `wxWidgets-3.2.2.1`
6. Type `./configure`
7. Type `make` (use the option `-j __` where the `_` is any number of threads you want to use to make this go faster). This step will take a while
8. `cd` into the parent folder (i.e. `cd ..`)
9. Type `make` to compile the project
10. Once finished, type `./a.out` to run the program
## Other Notes
- Make sure you CTRL-C after closing the program if the program has not already terminated before you run it again
- To view and modify the information on our database, we created an additional account, so go to <a href = "back4app.com"> Back4App </a> and login with the following credentials, and once done, go into "My Apps", then under the "EVNT" app, click the "Dashboard" button
    - Email: bllaaze4@gmail.com
    - Password: password

AUTHORS: John Krupa, Yash Gupta, Thai An-Luong, Andrew Kwan, Will Reil