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
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
	<link rel="stylesheet" type="text/css" href="<?php echo base_url();?>assets/css/custom.css">
</head>
</head>
<body>
	<header class="header-user-dropdown">
		<div class="header-limiter">
			<h1><a href="#">Cheap<span>Books</span></a></h1>
			<div class="header-user-menu">
			<div class="text"><?php echo $this->session->userdata('username'); ?></div>
				<ul>
					<li><div class="text" >Logged in user is - <?php echo $this->session->userdata('username');?></div></li>
					<li><a href="<?php echo base_url();?>shoppingcart/displayShoppingCart"><span class="glyphicon glyphicon-shopping-cart"></span>Shopping Basket</a></li>
					<li><a href="<?php echo base_url();?>users/logout" class="highlight">Logout</a></li>
				</ul>
			</div>
		</div>
	</header>
	<br/><br/><br/>

	<div class="container-fluid">
	   <div class="jumbotron changeJumboBackground" style="overflow: auto;">