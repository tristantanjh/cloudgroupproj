//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

import inet.mobility.contract.IMobility;
import inet.mobility.single.TurtleMobility;
import inet.visualizer.common.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;

simple CanNode
{
    parameters:
        int configType = default(1);
        @display("i=block/bucket");
    gates:
        input in[];
        output out[];
}


simple CloudNode
{
    parameters:
        int configType = default(1);
        @display("i=old/pc");
    gates:
        input in[];
        output out[];
}

simple Host
{
    parameters:
        @display("i=misc/cloud"); // add a default icon
        int sendMessagePowerCloud = default(0);
        int sendMessagePowerComp = default(0);
        int receiveMessagePowerCloud = default(0);
        int receiveMessagePowerComp = default(0);
        int sendMessageDelayCloud = default(0);
        int sendMessageDelayComp = default(0);
        int receiveMessageDelayCloud = default(0);
        int receiveMessageDelayComp = default(0);
    gates:
        input in[3];
        output out[3];
}

module TruckHost  {
    parameters:
        int configType = default(1);
        @display("i=device/pocketpc"); // add a default icon
	gates:
	    input in[];
	    output out[];
    submodules:
        mobility: <default("StationaryMobility")> like IMobility {
            @display("p=100,100;is=s");
        }
        host: Host;
    connections:
        host.out[0] --> out[0];
        host.in[0] <-- in[0];
        host.out[1] --> out[1];
        host.in[1] <-- in[1];
        host.out[2] --> out[2];
        host.in[2] <-- in[2];
}

network GarbageCollectionSystem
{
    parameters:
        int numHosts;
        @display("bgb=1271.9962,398.50125");
        @figure[backgroundText](type=text; pos=750,20; text="No garbage solution"; color=black; font="Arial, bold");
        @figure[text](type=text; pos=750,80; text="Slow connection from the smartphone to others (time it takes) = \nSlow connection from others to the smartphone (time it takes) = \nFast connection from the smartphone to others (time it takes) = \nFast connection from others to the smartphone (time it takes) = \n\nConnection from the can to others (time it takes) = \nConnection from others to the can (time it takes) = \n\nConnection from the anotherCan to others (time it takes) = \nConnection from others to the anotherCan (time it takes) = \n\nSlow connection from the Cloud to others (time it takes) = \nSlow connection from others to the Cloud (time it takes) = \nFast connection from the Cloud to others (time it takes) = \nFast connection from others to the Cloud (time it takes) ="; color=black; font="Arial, 5");
    submodules:
        can: CanNode {
            parameters:
                @display("p=215.54,60.1025;r=90;t=sentCanFast: 0 rcvdCanFast: 0 numberOfLostCanMsgs: 0");
        }
        anotherCan: CanNode {
            parameters:
                @display("p=215.54,223.105;r=90;t=sentAnotherCanFast: 0 rcvdAnotherCanFast: 0 numberOfLostAnotherCanMsgs: 0");
        }
        cloud: CloudNode {
            parameters:
                @display("p=548.1763,226.785;r=360");
        }
        host[numHosts]: TruckHost {
            parameters:
                @display("p=450.76874,100.51625;r=45;t=sentHostFast: 0 rcvdHostFast: 0 sentHostSlow: 0 rcvdHostSlow: 0");
        }
        visualizer: IntegratedVisualizer {
            @display("p=671.16,29.61");
        }
        physicalEnvironment: PhysicalEnvironment {
            parameters:
                @display("p=607.2425,328.49124");
        }
    connections:
        can.out++ --> {  delay = 100ms; } --> cloud.in++;
        can.in++ <-- {  delay = 100ms; } <-- cloud.out++;

        can.out++ --> {  delay = 100ms; } --> host[0].in++;
        can.in++ <-- {  delay = 100ms; } <-- host[0].out++;

        anotherCan.out++ --> {  delay = 100ms; } --> cloud.in++;
        anotherCan.in++ <-- {  delay = 100ms; } <-- cloud.out++;

        anotherCan.out++ --> {  delay = 100ms; } --> host[0].in++;
        anotherCan.in++ <-- {  delay = 100ms; } <-- host[0].out++;

        host[0].out++ --> {  delay = 100ms; } --> cloud.in++;
        host[0].in++ <-- {  delay = 100ms; } <-- cloud.out++;
}
