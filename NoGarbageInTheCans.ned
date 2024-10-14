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
        @display("bgb=691.1788,399.9925");
    submodules:
        can: CanNode {
            parameters:
                @display("p=215.54,60.1025;r=90");
        }
        anotherCan: CanNode {
            parameters:
                @display("p=215.54,203.105;r=90");
        }
        cloud: CloudNode {
            parameters:
                @display("p=548.1763,136.785;r=360");
        }
        host: TruckNode {
            parameters:
                @display("p=450.76874,100.51625;r=45");
        }
        host2[numHosts]: StandardHost {
            @display("i=misc/smartphone");
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
