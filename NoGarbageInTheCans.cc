#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class CanNode : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(CanNode);

void CanNode::initialize()
{
    cMessage *msg = new cMessage("I am Can Node");
    bubble("I am can node");
}

void CanNode::handleMessage(cMessage *msg)
{
    bubble("received");
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

class TruckNode : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(TruckNode);

void TruckNode::initialize()
{
    cMessage *msg = new cMessage("I am Truck Node");
    bubble("I am truck node");
}

void TruckNode::handleMessage(cMessage *msg)
{
    bubble("received");
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

class CloudNode : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(CloudNode);

void CloudNode::initialize()
{
    cMessage *msg = new cMessage("I am Cloud Node");
    bubble("I am Cloud node");
}

void CloudNode::handleMessage(cMessage *msg)
{
    bubble("received");
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

class VisualizerNode : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(VisualizerNode);

void VisualizerNode::initialize()
{
    cMessage *msg = new cMessage("I am Visualizer Node");
    bubble("I am Visualizer node");
}

void VisualizerNode::handleMessage(cMessage *msg)
{
    bubble("received");
}
