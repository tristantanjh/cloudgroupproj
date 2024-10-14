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
        input in;
        output out;
}

simple TruckNode
{
    parameters:
        @display("i=block/wheelbarrow");
    gates:
        input in;
        output out;
}

simple CloudNode
{
    parameters:
        @display("i=old/pc");
    gates:
        input in;
        output out;
}

simple VisualizerNode
{
    parameters:
        @display("i=block/app");
    gates:
        input in;
        output out;
}

network GarbageCollectionNetwork
{
    @display("bgb=825.60504,266.475");
    submodules:
        can: CanNode {
            parameters:
                @display("p=144.925,69.19");
        }
        anotherCan: CanNode {
            parameters:
                @display("p=181.39,218.79001");
        }
        cloud: CloudNode {
            parameters:
                @display("p=678.81,134.64");
        }
        host[0]: TruckNode {
            parameters:
                @display("p=505.83502,101.915");
        }
        visualizer: VisualizerNode {
            parameters:
                @display("p=453.475,32.725002");
        }
    connections:
        can.out --> {  delay = 100ms; } --> cloud.in;
        can.in <-- {  delay = 100ms; } <-- cloud.out;

        can.out --> {  delay = 100ms; } --> host[0].in;
        can.in <-- {  delay = 100ms; } <-- host[0].out;

        anotherCan.out --> {  delay = 100ms; } --> cloud.in;
        anotherCan.in <-- {  delay = 100ms; } <-- cloud.out;

        anotherCan.out --> {  delay = 100ms; } --> host[0].in;
        anotherCan.in <-- {  delay = 100ms; } <-- host[0].out;

        host[0].out --> {  delay = 100ms; } --> cloud.in;
        host[0].in <-- {  delay = 100ms; } <-- cloud.out;
}
