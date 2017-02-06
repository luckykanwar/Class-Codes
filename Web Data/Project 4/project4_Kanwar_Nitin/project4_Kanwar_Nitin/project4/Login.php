<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<script type="text/javascript" src="Javascript.js"></script>
	<link rel="stylesheet" type="text/css" href="style.css">
	<title>Login </title>
</head>
<body>
	<header class="header-user-dropdown">
		<div class="header-limiter">
			<h1><a href="#">Cheap<span>Books</span></a></h1>
		</div>
	</header>
	<br/><br/>
	<form class="login-block" action="Login.php" method="GET">
	    <h1>Login</h1>
	    <input type="text" value="" placeholder="Username" id="username" name="user" />
	    <input type="password" value="" placeholder="Password" id="password" name="pass" />
	    <input style="display:none" type="login" value="login" id="login" name="login"/>
 	    <button type="submit" value="submit">Login</button>
	    <br/><br/>
	    <button type="button" id="register" onclick="Redirect()">New User? Register Here</button>
	</form>
	<div class="container-fluid">
	    <div class="jumbotron changeJumboBackground" style="overflow: auto;">
			<?php
				$login = $_GET["login"];
			    if($login=="login")
			    {
			    	session_start();
					$user = $_GET["user"];
					//$pwd = md5($_GET["pswd"]);
					$pass = md5($_GET["pass"]);
					$servername = "localhost";
					$username = "root";
					$password = "backontrack";
					$dbname = "cheapbook";

					$conn = new mysqli($servername, $username, $password, $dbname);

					if ($conn->connect_error){
				    	die("Connection failed: " . $conn->connect_error);
					}
					$sql = "SELECT * FROM customers WHERE UserName='".$user."' AND Password='".$pass."'";
					//echo $sql;	

					$result = $conn->query($sql);
			
					if ($result->num_rows > 0){
						//echo "result is generated";
						$row = $result->fetch_assoc();
						$_SESSION["user"]=$user;
						$_SESSION["pass"]=$pass;
						echo '<script type="text/javascript">
							           window.location = "Account.php"
							  </script>';
					}
					else {
						echo '<script>alert("Incorrect username or password ! Please try again !")</script>';
				    	//header('Location: Login.php');
				    	session_destroy();
					}
					$conn.close();
			    }
			?>
		</div>
	</div>
</body>

</html>