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

simple CanNode
{
    parameters:
        @display("i=block/bucket");
    gates:
        input in[];
        output out[];
}

simple TruckNode
{
    parameters:
        @display("i=block/wheelbarrow");
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


network GarbageCollectionNetwork
{
    @display("bgb=825.60504,266.475");
    submodules:
        can: CanNode {
            parameters:
                @display("p=226.93875,62.175;r=90");
        }
        anotherCan: CanNode {
            parameters:
                @display("p=215.54,202.06876;r=90");
        }
        cloud: CloudNode {
            parameters:
                @display("p=555.43,137.82124;r=360");
        }
        host: TruckNode {
            parameters:
                @display("p=449.7325,83.93625;r=45");
        }
    connections:
        can.out++ --> {  delay = 100ms; } --> cloud.in++;
        can.in++ <-- {  delay = 100ms; } <-- cloud.out++;

        can.out++ --> {  delay = 100ms; } --> host.in++;
        can.in++ <-- {  delay = 100ms; } <-- host.out++;

        anotherCan.out++ --> {  delay = 100ms; } --> cloud.in++;
        anotherCan.in++ <-- {  delay = 100ms; } <-- cloud.out++;

        anotherCan.out++ --> {  delay = 100ms; } --> host.in++;
        anotherCan.in++ <-- {  delay = 100ms; } <-- host.out++;

        host.out++ --> {  delay = 100ms; } --> cloud.in++;
        host.in++ <-- {  delay = 100ms; } <-- cloud.out++;
}
