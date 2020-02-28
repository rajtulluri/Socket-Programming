#Network simulator object
set ns [new Simulator]
#Set color for data flows, here we have 2 flows hence -
$ns color 1 Blue
$ns color 2 Red
#open nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf
#Finish procedure for the end of simulation
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

#Creating 5 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

#Links between the nodes
$ns duplex-link $n0 $n4 2Mb 10ms DropTail
$ns duplex-link $n1 $n4 2Mb 10ms DropTail
$ns duplex-link $n2 $n4 2Mb 10ms DropTail
$ns duplex-link $n3 $n4 2Mb 10ms DropTail

#Setting Queue limit for node 4
$ns queue-limit $n4 $n2 10
$ns queue-limit $n4 $n3 15

#Orientation of Nodes
$ns duplex-link-op $n0 $n4 orient right-up
$ns duplex-link-op $n1 $n4 orient right-down
$ns duplex-link-op $n2 $n4 orient left-up
$ns duplex-link-op $n3 $n4 orient left-down

#Monitor merge Node queue
$ns duplex-link-op $n4 $n2 queuePos 0.5
$ns duplex-link-op $n4 $n3 queuePos 0.5
#Setup UDP source
set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp1
set null1 [new Agent/Null]
$ns attach-agent $n3 $null1
$ns connect $udp1 $null1
$udp1 set fid_ 1
#Set CBR over UDP connection
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1mb
$cbr1 set random_ false
#Set another UDP agent
set udp2 [new Agent/UDP]
$ns attach-agent $n1 $udp2
set null2 [new Agent/Null]
$ns attach-agent $n2 $null2
$ns connect $udp2 $null2
$udp2 set fid_ 2
#Set CBR over UDP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2
$cbr2 set type_ CBR
$cbr2 set packet_size_ 1000
$cbr2 set rate_ 1mb
$cbr2 set random_ false
#Schedule the events
$ns at 0.5 "$cbr1 start"
$ns at 1.5 "$cbr2 start"
$ns at 9.0 "$cbr1 stop"
$ns at 9.5 "$cbr2 stop"
#Detach udp and null agents
$ns at 9.6 "$ns detach-agent $n0 $udp1; $ns detach-agent $n3 $null1"
$ns at 9.6 "$ns detach-agent $n1 $udp2; $ns detach-agent $n2 $null2"
#Call Finish after 10 seconds of simulation
$ns at 10.0 "finish"
$ns run










