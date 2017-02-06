<!DOCTYPE html>
<html>
<head>
	<title>
		<?php 
			echo 'ShoppingCart of ' . $this->session->userdata('username');
		?>
	</title>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	
</head>
<body>
	<header class="header-user-dropdown">
		<div class="header-limiter">
			<h1><a href="#">Cheap<span>Books</span></a></h1>
			<div class="header-user-menu">
			<div class="text"><!--<?php echo $this->session->userdata('username'); ?>--></div>
				<ul>
					<li><div class="text" >Logged in user is - <?php echo $this->session->userdata('username');?></div></li>
					<li><a href="shoppingcart/displayShoppingCart"><span class="glyphicon glyphicon-shopping-cart"></span>Shopping Basket</a></li>
					<li><a href="users/logout" class="highlight">Logout</a></li>
				</ul>
			</div>
		</div>
	</header>
	<br/><br/><br/>

	   