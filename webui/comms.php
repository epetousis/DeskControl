<?php
error_reporting(~E_WARNING);
 
$server = '127.0.0.1';
$port = 41585;
 
if(!($sock = socket_create(AF_INET, SOCK_DGRAM, 0)))
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Couldn't create socket: [$errorcode] $errormsg \n");
}

if ($_POST["setChannel"]) {
	$command = 0x90;
	$bank = 0x00;
	if ($_POST["setChannel"]=="off") {
		$command = 0x80;
	}
	if ($_POST["bank"] == "1") {
		$bank = 0x01;
	}
	$channel = intval($_POST["channel"]);
	socket_sendto($sock, pack("C*", $command, $bank, $channel) , 3, 0 , $server , $port);
}/* elseif ($_POST["getChannel"]) {
	socket_sendto($sock, chr(0x42) , strlen($input) , 0 , $server , $port);
	socket_recv ( $sock , $reply , 2045 , MSG_WAITALL ) === FALSE
}*/
socket_close($sock);
?>