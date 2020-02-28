#Network simulator object
set ns [new Simulator]
#Set color for data flows, here we have 2 flows hence -
$ns color 1 Blue
$ns color 2 Red
$ns color 3 Yellow
$ns color 4 Green
$ns color 5 Black
$ns color 6 Grey
#open nam trace file
set nf [open out3.nam w]
$ns namtrace-all $nf
#Finish procedure for the end of simulation
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out3.nam &
	exit 0
}

#Creating 5 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]
#Links between the nodes
$ns duplex-link $n0 $n1 1.5Mb 40ms DropTail
$ns duplex-link $n1 $n7 10Mb 20ms DropTail
$ns duplex-link $n1 $n8 10Mb 20ms DropTail
$ns duplex-link $n1 $n9 10Mb 20ms DropTail
$ns duplex-link $n1 $n10 10Mb 20ms DropTail
$ns duplex-link $n1 $n11 10Mb 20ms DropTail
$ns duplex-link $n0 $n2 10Mb 20ms DropTail
$ns duplex-link $n0 $n3 10Mb 20ms DropTail
$ns duplex-link $n0 $n4 10Mb 20ms DropTail
$ns duplex-link $n0 $n5 10Mb 20ms DropTail
$ns duplex-link $n0 $n6 10Mb 20ms DropTail
#Orientation of Nodes
$ns duplex-link-op $n1 $n7 orient up
$ns duplex-link-op $n1 $n8 orient left-up
$ns duplex-link-op $n1 $n9 orient left
$ns duplex-link-op $n1 $n10 orient left-down
$ns duplex-link-op $n1 $n11 orient down
$ns duplex-link-op $n0 $n2 orient up
$ns duplex-link-op $n0 $n3 orient right-up
$ns duplex-link-op $n0 $n4 orient right
$ns duplex-link-op $n0 $n5 orient right-down
$ns duplex-link-op $n0 $n6 orient down
$ns duplex-link-op $n0 $n1 orient left
#Set TCP connection
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n7 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $sink1
$ns attach-agent $n3 $sink1
$ns attach-agent $n4 $sink1
$ns attach-agent $n5 $sink1
$ns attach-agent $n6 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1
#Set TCP connection
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
$ns attach-agent $n8 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n2 $sink2
$ns attach-agent $n3 $sink2
$ns attach-agent $n4 $sink2
$ns attach-agent $n5 $sink2
$ns attach-agent $n6 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2
#Set TCP connection
set tcp3 [new Agent/TCP]
$tcp3 set class_ 2
$ns attach-agent $n9 $tcp3
set sink3 [new Agent/TCPSink]
$ns attach-agent $n2 $sink3
$ns attach-agent $n3 $sink3
$ns attach-agent $n4 $sink3
$ns attach-agent $n5 $sink3
$ns attach-agent $n6 $sink3
$ns connect $tcp3 $sink3
$tcp3 set fid_ 3
#Set TCP connection
set tcp4 [new Agent/TCP]
$tcp4 set class_ 2
$ns attach-agent $n10 $tcp4
set sink4 [new Agent/TCPSink]
$ns attach-agent $n2 $sink4
$ns attach-agent $n3 $sink4
$ns attach-agent $n4 $sink4
$ns attach-agent $n5 $sink4
$ns attach-agent $n6 $sink4
$ns connect $tcp4 $sink4
$tcp4 set fid_ 4
#Set TCP connection
set tcp5 [new Agent/TCP]
$tcp4 set class_ 2
$ns attach-agent $n11 $tcp5
set sink5 [new Agent/TCPSink]
$ns attach-agent $n2 $sink5
$ns attach-agent $n3 $sink5
$ns attach-agent $n4 $sink5
$ns attach-agent $n5 $sink5
$ns attach-agent $n6 $sink5
$ns connect $tcp5 $sink5
$tcp5 set fid_ 5


#Set TCP connection
set tcp7 [new Agent/TCP]
$tcp7 set class_ 2
$ns attach-agent $n2 $tcp7
set sink7 [new Agent/TCPSink]
$ns attach-agent $n7 $sink7
$ns attach-agent $n8 $sink7
$ns attach-agent $n9 $sink7
$ns attach-agent $n10 $sink7
$ns attach-agent $n11 $sink7
$ns connect $tcp7 $sink7
$tcp7 set fid_ 1
#Set TCP connection
set tcp8 [new Agent/TCP]
$tcp8 set class_ 2
$ns attach-agent $n3 $tcp8
set sink8 [new Agent/TCPSink]
$ns attach-agent $n7 $sink8
$ns attach-agent $n8 $sink8
$ns attach-agent $n9 $sink8
$ns attach-agent $n10 $sink8
$ns attach-agent $n11 $sink8
$ns connect $tcp8 $sink8
$tcp8 set fid_ 2
#Set TCP connection
set tcp9 [new Agent/TCP]
$tcp9 set class_ 2
$ns attach-agent $n4 $tcp9
set sink9 [new Agent/TCPSink]
$ns attach-agent $n7 $sink9
$ns attach-agent $n8 $sink9
$ns attach-agent $n9 $sink9
$ns attach-agent $n10 $sink9
$ns attach-agent $n11 $sink9
$ns connect $tcp9 $sink9
$tcp9 set fid_ 3
#Set TCP connection
set tcp10 [new Agent/TCP]
$tcp10 set class_ 2
$ns attach-agent $n5 $tcp10
set sink10 [new Agent/TCPSink]
$ns attach-agent $n7 $sink10
$ns attach-agent $n8 $sink10
$ns attach-agent $n9 $sink10
$ns attach-agent $n10 $sink10
$ns attach-agent $n11 $sink10
$ns connect $tcp10 $sink10
$tcp10 set fid_ 4
#Set TCP connection
set tcp11 [new Agent/TCP]
$tcp11 set class_ 2
$ns attach-agent $n6 $tcp11
set sink11 [new Agent/TCPSink]
$ns attach-agent $n7 $sink11
$ns attach-agent $n8 $sink11
$ns attach-agent $n9 $sink11
$ns attach-agent $n10 $sink11
$ns attach-agent $n11 $sink11
$ns connect $tcp11 $sink11
$tcp11 set fid_ 5


#Set CBR over UDP connection
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $tcp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1mb
$cbr1 set random_ false
#Set CBR over UDP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $tcp2
$cbr2 set type_ CBR
$cbr2 set packet_size_ 1000
$cbr2 set rate_ 1mb
$cbr2 set random_ false
#Set CBR over UDP connection
set cbr3 [new Application/Traffic/CBR]
$cbr3 attach-agent $tcp3
$cbr3 set type_ CBR
$cbr3 set packet_size_ 1000
$cbr3 set rate_ 1mb
$cbr3 set random_ false
#Set CBR over UDP connection
set cbr4 [new Application/Traffic/CBR]
$cbr4 attach-agent $tcp4
$cbr4 set type_ CBR
$cbr4 set packet_size_ 1000
$cbr4 set rate_ 1mb
$cbr4 set random_ false
#Set CBR over UDP connection
set cbr5 [new Application/Traffic/CBR]
$cbr5 attach-agent $tcp5
$cbr5 set type_ CBR
$cbr5 set packet_size_ 1000
$cbr5 set rate_ 1mb
$cbr5 set random_ false

#Set CBR over UDP connection
set cbr7 [new Application/Traffic/CBR]
$cbr7 attach-agent $tcp7
$cbr7 set type_ CBR
$cbr7 set packet_size_ 1000
$cbr7 set rate_ 1mb
$cbr7 set random_ false
#Set CBR over UDP connection
set cbr8 [new Application/Traffic/CBR]
$cbr8 attach-agent $tcp8
$cbr8 set type_ CBR
$cbr8 set packet_size_ 1000
$cbr8 set rate_ 1mb
$cbr8 set random_ false
#Set CBR over UDP connection
set cbr9 [new Application/Traffic/CBR]
$cbr9 attach-agent $tcp9
$cbr9 set type_ CBR
$cbr9 set packet_size_ 1000
$cbr9 set rate_ 1mb
$cbr9 set random_ false
#Set CBR over UDP connection
set cbr10 [new Application/Traffic/CBR]
$cbr10 attach-agent $tcp10
$cbr10 set type_ CBR
$cbr10 set packet_size_ 1000
$cbr10 set rate_ 1mb
$cbr10 set random_ false
#Set CBR over UDP connection
set cbr11 [new Application/Traffic/CBR]
$cbr11 attach-agent $tcp11
$cbr11 set type_ CBR
$cbr11 set packet_size_ 1000
$cbr11 set rate_ 1mb
$cbr11 set random_ false

#Schedule the events
$ns at 0.5 "$cbr1 start"
$ns at 1.5 "$cbr2 start"
$ns at 1.5 "$cbr3 start"
$ns at 1.5 "$cbr4 start"
$ns at 1.5 "$cbr5 start"
# $ns at 1.5 "$cbr7 start"
# $ns at 1.5 "$cbr8 start"
# $ns at 1.5 "$cbr9 start"
# $ns at 1.5 "$cbr10 start"
# $ns at 1.5 "$cbr11 start"
$ns at 9.0 "$cbr1 stop"
$ns at 9.5 "$cbr2 stop"
$ns at 9.0 "$cbr3 stop"
$ns at 9.5 "$cbr4 stop"
$ns at 9.0 "$cbr5 stop"
# $ns at 9.5 "$cbr7 stop"
# $ns at 9.0 "$cbr8 stop"
# $ns at 9.5 "$cbr9 stop"
# $ns at 9.0 "$cbr10 stop"
# $ns at 9.5 "$cbr11 stop"
#Call Finish after 10 seconds of simulation
$ns at 10.0 "finish"
$ns run

