<?php
	class Shoppingcart extends CI_Controller{
		public function index(){
			$this->load->view('layouts/headerMainPage');
			$this->load->view('shopping/default');
			$this->load->view('layouts/footer');
		}	

		public function displayShoppingCart(){
			$data['result'] = $this->Shoppingcart_model->fetchShoppingHistory();
			if(count($data['result']) > 0){
				$this->load->view('layouts/headerMainPage');
				$this->load->view('shopping/history',$data);
			//	$this->load->view('layouts/footer');
			}

			$data['result'] = $this->Shoppingcart_model->fetchShoppingCart();
			if(count($data['result']) > 0){
					//$this->load->view('layouts/header');
					$this->load->view('shopping/default',$data);
					$this->load->view('layouts/footer');
			}
			else{
				$this->session->set_flashdata('no_data_in_cart','There is no data in your cart ! Please go back and add books !');
				//$this->load->view('layouts/header');
				$this->load->view('shopping/default');
				$this->load->view('layouts/footer');
			}
		}

		public function buyShoppingCart(){
			$result = $this->Shoppingcart_model->buyShoppingCart();
			if($result > 0){
				$this->session->set_userdata('bookCount',0);
				$this->session->set_flashdata('shipped','Your order has been placed and books have been dispatched ! Your current cart has been cleared ! Please go back and add books to the cart again !');
				$this->load->view('layouts/headerMainPage');
				$this->load->view('shopping/default');
				$this->load->view('layouts/footer');

			}
		}
	}
?>