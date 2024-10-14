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
    send(msg, "out", 0);
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
    private:
        cMessage *msgDelay;
};

Define_Module(TruckNode);

void TruckNode::initialize()
{
    cMessage *msg = new cMessage("I am Truck Node");
    send(msg, "out", 0);
    msgDelay = new cMessage("msgDelay");
    scheduleAt(simTime() + 4.0, msgDelay);

}

void TruckNode::handleMessage(cMessage *msg)
{
    bubble("received");

    if (msg == msgDelay) {
        // This block is executed when the delayed message is triggered
        EV << "Message sent after delay!" << endl;
        bubble("hi");

        // Send the message through the specified output gate by index
        send(msg, "out"); // "out" is the base name of the gates, targetGateIndex is the gate index
    } else {
        // Handle other messages here if needed
    }
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
}

void VisualizerNode::handleMessage(cMessage *msg)
{
    bubble("received");
}
