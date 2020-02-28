#Network simulator object
set ns [new Simulator]
#Set color for data flows, here we have 2 flows hence -
$ns color 1 Blue
$ns color 2 Red
#open nam trace file
set nf [open out2.nam w]
$ns namtrace-all $nf
#Finish procedure for the end of simulation
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out2.nam &
	exit 0
}

#Creating 5 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
#Links between the nodes
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n0 1Mb 10ms DropTail
#Orientation of Nodes
$ns duplex-link-op $n0 $n1 orient left-up
$ns duplex-link-op $n1 $n2 orient left-down
$ns duplex-link-op $n2 $n3 orient right-down
$ns duplex-link-op $n3 $n0 orient right-up
#Set TCP connection
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1
#Set FTP over tcp
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP
#Set TCP connection
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
$ns attach-agent $n2 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2
#Set FTP over tcp
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP
#Schedule the events
$ns at 0.5 "$ftp1 start"
$ns at 1.5 "$ftp2 start"
$ns at 9.0 "$ftp1 stop"
$ns at 9.5 "$ftp2 stop"
#Detach tcp and sink agents
$ns at 9.6 "$ns detach-agent $n0 $tcp1; $ns detach-agent $n1 $sink1"
$ns at 9.6 "$ns detach-agent $n2 $tcp2; $ns detach-agent $n3 $sink2"
#Demonstrate Link failure at time 4.5 sec
$ns rtmodel-at 4.5 down $n0 $n1
#Call Finish after 10 seconds of simulation
$ns at 10.0 "finish"
$ns run
