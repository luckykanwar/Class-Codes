<?php
	class User_model extends CI_Model{
		public function create_member(){
			//$enc_password = md5($this->input->post('password'));
			$data = array(
						'username' 	=> $this->input->post('username'),
						'password' 	=> $this->input->post('password'),
						'address' 	=> $this->input->post('address'),
						'phone' 	=> $this->input->post('phone'),
						'email' 	=> $this->input->post('email')
					);	 
			$insertCustomer = $this->db->insert('customers', $data);
			$basket = array(
						'username' => $this->input->post('username')
						);
			$insertBasketId = $this->db->insert('shoppingbasket', $basket);
			return $insertCustomer;
		}

		public function login_user($username, $password){
			//$enc_password = md5($password);
			$this->db->select('customers.username, shoppingbasket.basketid');
			$this->db->from('customers');
			$this->db->join('shoppingbasket','customers.username = shoppingbasket.username');
			$this->db->where('customers.username',$username);
			$this->db->where('customers.password',$password);
			//echo $this->db->get_compiled_select();
			$query = $this->db->get();
			if($query->num_rows() > 0){
				return $query->result();
			}
			else{
				return false;
			}
		}

		public function logout_user(){
			$this->db->where('basketid', $this->session->userdata('basketid'));
			$this->db->delete('contains'); 
		}
	}
?>