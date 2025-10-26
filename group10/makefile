a.out: AccountInfo.o App.o home.o MainFrame.o Reset.o SignUp.o CreateEvent.o userdbhandler.o invitedbhandler.o eventdbhandler.o database_handler.o Edit.o DisplayEvent.o
	g++ -std=c++11 AccountInfo.o App.o home.o MainFrame.o Reset.o SignUp.o CreateEvent.o userdbhandler.o invitedbhandler.o eventdbhandler.o database_handler.o Edit.o DisplayEvent.o `wx-config --cxxflags --libs`

AccountInfo.o: AccountInfo.cpp
	g++ -std=c++11 -c AccountInfo.cpp `wx-config --cxxflags --libs`

App.o: App.cpp
	g++ -std=c++11 -c App.cpp `wx-config --cxxflags --libs`

home.o: home.cpp
	g++ -std=c++11 -c home.cpp `wx-config --cxxflags --libs`

MainFrame.o: MainFrame.cpp
	g++ -std=c++11 -c MainFrame.cpp `wx-config --cxxflags --libs`

Reset.o: Reset.cpp
	g++ -std=c++11 -c Reset.cpp `wx-config --cxxflags --libs`

SignUp.o: SignUp.cpp
	g++ -std=c++11 -c SignUp.cpp `wx-config --cxxflags --libs`

CreateEvent.o: CreateEvent.cpp
	g++ -std=c++11 -c CreateEvent.cpp `wx-config --cxxflags --libs`

Edit.o: Edit.cpp
	g++ -std=c++11 -c Edit.cpp `wx-config --cxxflags --libs`
	
DisplayEvent.o: DisplayEvent.cpp
	g++ -std=c++11 -c DisplayEvent.cpp `wx-config --cxxflags --libs`

userdbhandler.o: ./dbhandler/userdbhandler.cpp
	g++ -std=c++11 -c ./dbhandler/userdbhandler.cpp

invitedbhandler.o: ./dbhandler/invitedbhandler.cpp
	g++ -std=c++11 -c ./dbhandler/invitedbhandler.cpp

eventdbhandler.o: ./dbhandler/eventdbhandler.cpp
	g++ -std=c++11 -c ./dbhandler/eventdbhandler.cpp

database_handler.o: ./dbhandler/database_handler.cpp
	g++ -std=c++11 -c ./dbhandler/database_handler.cpp

clean:
	rm *.o a.out
