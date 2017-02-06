<?php 
	if($this->session->flashdata('registered')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('registered');
		echo '</p>';
	}

	if($this->session->flashdata('login_falied')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('login_falied');
		echo '</p>';
	}

	if($this->session->flashdata('logged_out')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('logged_out');
		echo '</p>';
	}

	if($this->session->flashdata('need_login')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('need_login');
		echo '</p>';
	}
?>
<p><h3 style="font-weight: bold; text-align: center">Welcome to cheapbooks ! Your home to affordable books and unlimited reading !</h3></p>
