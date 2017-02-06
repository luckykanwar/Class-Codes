<?php
	class Shoppingcart_model extends CI_Model{
		public function fetchShoppingCart(){
			$this->db->select('author.name as author_name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name as warehousename, sum(contains.number) as numberInBasket,sum(contains.number)*book.price as price');
			$this->db->from('contains');
			$this->db->join('shoppingbasket', 'contains.basketid = shoppingbasket.basketid');
			$this->db->join('warehouse', 'contains.warehousecode = warehouse.warehousecode');
			$this->db->join('book', 'book.isbn = contains.isbn');
			$this->db->join('writtenby', 'book.isbn = writtenby.isbn');
			$this->db->join('author', 'author.ssn = writtenby.ssn');
			$this->db->where('shoppingbasket.username', $this->session->userdata('username')); 
			$this->db->group_by('author.name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name'); 
			$query = $this->db->get();
			if($query->num_rows() > 0){
				return $query->result();
			}
		}	
		
		public function buyShoppingCart(){
			$this->db->select('author.name as author_name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name as warehousename, sum(contains.number) as numberInBasket,sum(contains.number)*book.price as price');
			$this->db->from('contains');
			$this->db->join('shoppingbasket', 'contains.basketid = shoppingbasket.basketid');
			$this->db->join('warehouse', 'contains.warehousecode = warehouse.warehousecode');
			$this->db->join('book', 'book.isbn = contains.isbn');
			$this->db->join('writtenby', 'book.isbn = writtenby.isbn');
			$this->db->join('author', 'author.ssn = writtenby.ssn');
			$this->db->where('shoppingbasket.username', $this->session->userdata('username')); 
			$this->db->group_by('author.name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name'); 
			$query = $this->db->get();
			$inserted = 0;
			if($query->num_rows() > 0){
				foreach($query->result() as $result){
					$data = array(
									'isbn'			=> $result->isbn,	
									'warehousecode' => $result->warehousecode,
									'username'		=> $this->session->userdata('username'),
									'number'		=> $result->numberInBasket
								);
					$insert = $this->db->insert('shippingorder',$data);
					$inserted = $inserted + 1;
				}
				$this->db->where('basketid', $this->session->userdata('basketid'));
				$this->db->delete('contains'); 
				return $inserted;
			}
		}

		public function fetchShoppingHistory(){
			$this->db->select('author.name as author_name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name as warehousename, sum(shippingorder.number) as numberInBasket,sum(shippingorder.number)*book.price as price');
			$this->db->from('shippingorder');
			$this->db->join('shoppingbasket', 'shippingorder.username = shoppingbasket.username');
			$this->db->join('warehouse', 'shippingorder.warehousecode = warehouse.warehousecode');
			$this->db->join('book', 'book.isbn = shippingorder.isbn');
			$this->db->join('writtenby', 'book.isbn = writtenby.isbn');
			$this->db->join('author', 'author.ssn = writtenby.ssn');
			$this->db->where('shoppingbasket.username', $this->session->userdata('username')); 
			$this->db->group_by('author.name,book.title,book.isbn,shoppingbasket.basketid,warehouse.warehousecode,warehouse.name'); 
			$query = $this->db->get();
			if($query->num_rows() > 0){
				return $query->result();
			}
		}	
	}
?>