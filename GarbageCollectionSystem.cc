#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class CanNode : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void updateDisplay();
        void updateDisplay2();
        virtual void noGarbageBehavior(cMessage *msg);
        virtual void slowGarbageBehavior(cMessage *msg);
        virtual void fastGarbageBehavior(cMessage *msg);
        virtual void finish() override;
    private:
        int msgCounter;
        int msgCounter2;
        int numberOfLostCanMsgs;
        int sentCanFast;
        int rcvdCanFast;
        int numberOfLostCanMsgs2;
        int sentCanFast2;
        int rcvdCanFast2;
        int configType;  // define behaviour of node based on config
};

Define_Module(CanNode);

void CanNode::initialize()
{
    // init variables
    msgCounter = 0;
    msgCounter2 = 0;
    numberOfLostCanMsgs = 0;
    sentCanFast = 0;
    rcvdCanFast = 0;
    numberOfLostCanMsgs2 = 0;
    sentCanFast2 = 0;
    rcvdCanFast2 = 0;

    configType = par("configType");
}

void CanNode::handleMessage(cMessage *msg)
{
    if (configType == 1) {
        noGarbageBehavior(msg);
    } else if (configType == 2) {
        slowGarbageBehavior(msg);
    } else {
        fastGarbageBehavior(msg);
    }
}

void CanNode::noGarbageBehavior(cMessage *msg)
{
    if (strcmp(msg->getName(), "1-Is the can full?") == 0){
        if (msgCounter >= 3) {
            EV << "final msg of this trash can";
            cMessage *newMsg = new cMessage("2-NO");

            sentCanFast++;
            rcvdCanFast++;
            updateDisplay();

            send(newMsg, "out", 1);
        } else {
            numberOfLostCanMsgs++;
            updateDisplay();
            bubble("Lost Message");
        }
        msgCounter++;
    } else if (strcmp(msg->getName(), "4-Is the can full?") == 0){
        if (msgCounter2 >= 3) {
            EV << "final msg of this trash can";
            cMessage *newMsg = new cMessage("5-NO");

            sentCanFast2++;
            rcvdCanFast2++;
            updateDisplay2();

            send(newMsg, "out", 1);
        } else {
            numberOfLostCanMsgs2++;
            updateDisplay2();
            bubble("Lost Message");
        }
        msgCounter2++;
    }
}

void CanNode::slowGarbageBehavior(cMessage *msg)
{
    if (msgCounter >= 3) {
        EV << "final msg of this trash can";
        cMessage *newMsg = new cMessage("3-YES");
        send(newMsg, "out", 1);
    } else {
        bubble("Lost Message");
    }
    msgCounter++;
}

void CanNode::fastGarbageBehavior(cMessage *msg)
{

}

void CanNode::finish()
{
    cModule *network = getParentModule();

    cCanvas *canvas = network->getCanvas();

    cTextFigure *textFigureHost = check_and_cast<cTextFigure*>(canvas->getFigure("hostText"));
    cTextFigure *textFigureCan = check_and_cast<cTextFigure*>(canvas->getFigure("canText"));
    cTextFigure *textFigureAnotherCan = check_and_cast<cTextFigure*>(canvas->getFigure("anotherCanText"));
    cTextFigure *textFigureCloud = check_and_cast<cTextFigure*>(canvas->getFigure("cloudText"));

    if (configType == 1) {
        textFigureHost->setText("Slow connection from the smartphone to others (time it takes) = 0\nSlow connection from others to the smartphone (time it takes) = 0\nFast connection from the smartphone to others (time it takes) = 800\nFast connection from others to the smartphone (time it takes) = 200\n\n");

        textFigureCan->setText("Connection from the can to others (time it takes) = 100\nConnection from others to the can (time it takes) = 100\n\n");

        textFigureAnotherCan->setText("Connection from the anotherCan to others (time it takes) = 100\nConnection from others to the anotherCan (time it takes) = 100\n\n");

        textFigureCloud->setText("Slow connection from the Cloud to others (time it takes) = 0\nSlow connection from others to the Cloud (time it takes) = 0\nFast connection from the Cloud to others (time it takes) = 0\nFast connection from others to the Cloud (time it takes) = 0");
    }
}

void CanNode::updateDisplay()
{
    char displayText[64];
    sprintf(displayText, "sentCanFast: %d rcvdCanFast: %d numberOfLostCanMsgs: %d", sentCanFast, rcvdCanFast, numberOfLostCanMsgs);
    getDisplayString().setTagArg("t", 0, displayText);
}

void CanNode::updateDisplay2()
{
    char displayText[64];
    sprintf(displayText, "sentAnotherCanFast: %d rcvdAnotherCanFast: %d numberOfLostAnotherCanMsgs: %d", sentCanFast2, rcvdCanFast2, numberOfLostCanMsgs2);
    getDisplayString().setTagArg("t", 0, displayText);
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

class Host : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void updateDisplay();
        virtual void noGarbageBehavior(cMessage *msg);
        virtual void slowGarbageBehavior(cMessage *msg);
        virtual void fastGarbageBehavior(cMessage *msg);
    private:
        cMessage *msgDelay;
        cMessage *timeoutEvent;
        simtime_t initialDelay;  // how long before sending 1st msg
        simtime_t timeout;  // how long to consider as timeout
        int timeoutCounter;
        int trashCanInteracted;
        int sentHostFast;
        int rcvdHostFast;
        int sentHostSlow;
        int rcvdHostSlow;
        int configType;  // define behaviour of node based on config
};

Define_Module(Host);

void Host::initialize()
{
    // init variables
    initialDelay = 4.0;
    timeout = 1.0;
    timeoutCounter = 0;
    trashCanInteracted = 0;
    sentHostFast = 0;
    rcvdHostFast = 0;
    sentHostSlow = 0;
    rcvdHostSlow = 0;
    
    configType = this->getParentModule()->par("configType");

    // first message
    msgDelay = new cMessage("msgDelay");
    scheduleAt(simTime() + initialDelay, msgDelay);

    // first timeout
    timeoutEvent = new cMessage("first timeout");
    scheduleAt(simTime() + initialDelay + timeout, timeoutEvent);

}

void Host::handleMessage(cMessage *msg)
{
    if (configType == 1) {
        noGarbageBehavior(msg);
    } else if (configType == 2) {
        slowGarbageBehavior(msg);
    } else {
        fastGarbageBehavior(msg);
    }
}

void Host::noGarbageBehavior(cMessage *msg)
{
    if (msg == msgDelay) {
        if (trashCanInteracted == 0) {
            // This block is executed when the delayed message is triggered
            EV << "Initial Message at t=4.0" << endl;

            // Send the message through the specified output gate by index
            cMessage *firstMessage = new cMessage("1-Is the can full?");
            sentHostFast++;

            updateDisplay();
            send(firstMessage, "out", 0); // "out" is the base name of the gates, targetGateIndex is the gate index
        } else if (trashCanInteracted == 1) {
            // This block is executed when the delayed message is triggered
            EV << "first message to 2nd trashcan" << endl;

            // Send the message through the specified output gate by index
            cMessage *secondMessage = new cMessage("4-Is the can full?");
            sentHostFast++;
            updateDisplay();
            send(secondMessage, "out", 1); // "out" is the base name of the gates, targetGateIndex is the gate index
        }

    } else if (msg == timeoutEvent) {
        // Handle timeout events for interaction with first trash can
        if (timeoutCounter < 3) {
            if (trashCanInteracted == 0) {
                cMessage *newMsg = new cMessage("1-Is the can full?");
                send(newMsg, "out", 0);
                sentHostFast++;
                updateDisplay();

            } else if (trashCanInteracted == 1) {
                cMessage *newMsg = new cMessage("4-Is the can full?");
                send(newMsg, "out", 1);
                sentHostFast++;
                updateDisplay();
            }
            EV << "Timeout expired, resending message and restarting timer\n";
            scheduleAt(simTime()+timeout, timeoutEvent);
            timeoutCounter++;
        }
    } else if (strcmp(msg->getName(), "2-NO") == 0){
        timeoutCounter = 0;  //reset timeout counter
        trashCanInteracted++;  // add 1 to trash counter
        rcvdHostFast++;
        updateDisplay();

        // send first message to 2nd trash can
        msgDelay = new cMessage("msgDelay");
        scheduleAt(simTime() + initialDelay, msgDelay);

        // second timeout event to 2nd trash can
        timeoutEvent = new cMessage("second timeout");
        scheduleAt(simTime() + initialDelay + timeout, timeoutEvent);
    } else if (strcmp(msg->getName(), "5-NO") == 0){
        timeoutCounter = 0;  //reset timeout counter
        trashCanInteracted++;  // add 1 to trash counter
        rcvdHostFast++;
        updateDisplay();
    }
}

void Host::slowGarbageBehavior(cMessage *msg)
{
    if (msg == msgDelay) {
        EV << "Initial Message at t=4.0" << endl;

        // Send the message through the specified output gate by index
        cMessage *firstMessage = new cMessage("1-Is the can full?");
        send(firstMessage, "out", 0); // "out" is the base name of the gates, targetGateIndex is the gate index
    } else if (msg == timeoutEvent) {
        // Handle timeout events for interaction with first trash can
        if (timeoutCounter < 3) {
            cMessage *newMsg = new cMessage("1-Is the can full?");
            send(newMsg, "out", 0);

            EV << "Timeout expired, resending message and restarting timer\n";
            scheduleAt(simTime()+timeout, timeoutEvent);
            timeoutCounter++;

        }
    }
}

void Host::fastGarbageBehavior(cMessage *msg)
{

}

void Host::updateDisplay()
{
    char displayText[64];

    sprintf(displayText, "sentHostFast: %d rcvdHostFast: %d sentHostSlow: %d rcvdHostSlow: %d", sentHostFast, rcvdHostFast, sentHostSlow, rcvdHostSlow);
    getParentModule()->getDisplayString().setTagArg("t", 0, displayText);
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
