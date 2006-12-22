// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Parser.h>
#include <Ice/Application.h>

using namespace std;

class LibraryClient : public Ice::Application
{
    virtual int run(int argc, char* argv[]);
    virtual void interruptCallback(int);
};

int
main(int argc, char* argv[])
{
    LibraryClient app;
    return app.main(argc, argv, "config.client");
}

int
LibraryClient::run(int argc, char* argv[])
{
    //
    // Since this is an interactive demo we want the custom interrupt
    // callback to be called when the process is interrupted.
    //
    userCallbackOnInterrupt();

    int runParser(int, char*[], const Ice::CommunicatorPtr&);
    return runParser(argc, argv, communicator());
}

void
LibraryClient::interruptCallback(int)
{
    try
    {
	communicator()->destroy();
    }
    catch(const IceUtil::Exception& ex)
    {
	cerr << appName() << ": " << ex << endl;
    }
    catch(...)
    {
	cerr << appName() << ": unknown exception" << endl;
    }
    exit(EXIT_SUCCESS);
}
