<?php
	class Home extends CI_Controller{
		public function index(){
			$this->load->view('layouts/header');
			$this->load->view('home');
			$this->load->view('users/login');
			$this->load->view('layouts/footer');
		}		
	}
?>