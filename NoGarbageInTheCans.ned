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

import inet.node.inet.StandardHost;
import inet.visualizer.common.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;

simple CanNode
{
    parameters:
        @display("i=block/bucket");
    gates:
        input in[];
        output out[];
}


simple CloudNode
{
    parameters:
        @display("i=old/pc");
    gates:
        input in[];
        output out[];
}

module TruckNode extends StandardHost
{
    gates:
        input in[];
        output out[];
}

network GarbageCollectionNetwork
{
    parameters:
        int numHosts;
        @display("bgb=983,399");
        @figure[backgroundText](type=text; pos=700,50; text="This is a background message"; color=black);
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
        host[numHosts]: TruckNode {
            parameters:
                @display("p=450.76874,100.51625;r=45;t=sentHostFast: 0 rcvdHostFast: 0 sentHostSlow: 0 rcvdHostSlow: 0");
        }
        visualizer: IntegratedVisualizer {
            @display("p=50,50");
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
