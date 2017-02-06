<?php
	class Search_model extends CI_Model{
		public function getSearchByAuthor($searchkey){
			$this->db->select('book.isbn,book.title,book.price,book.publisher, author.name as author_name, stocks.number, warehouse.name, warehouse.warehousecode');
			$this->db->from('book');
			$this->db->join('writtenby', 'book.isbn = writtenby.isbn');
			$this->db->join('author', 'author.ssn = writtenby.ssn');
			$this->db->join('stocks', 'stocks.isbn = book.isbn');
			$this->db->join('warehouse', 'warehouse.warehousecode = stocks.warehousecode');
			$this->db->where('stocks.number>', 0); 
			$this->db->like('author.name', $searchkey , 'both'); 

			$query = $this->db->get();
			if($query->num_rows() > 0){
				return $query->result();
			}
		}	

		public function getSearchByTitle($searchkey){
			$this->db->select('book.isbn,book.title,book.price,book.publisher, author.name as author_name, stocks.number, warehouse.name, warehouse.warehousecode');
			$this->db->from('book');
			$this->db->join('writtenby', 'book.isbn = writtenby.isbn');
			$this->db->join('author', 'author.ssn = writtenby.ssn');
			$this->db->join('stocks', 'stocks.isbn = book.isbn');
			$this->db->join('warehouse', 'warehouse.warehousecode = stocks.warehousecode');
			$this->db->where('stocks.number>', 0); 
			$this->db->like('book.title', $searchkey , 'both'); 

			$query = $this->db->get();
			if($query->num_rows() > 0){
				return $query->result();
			}
		}

		public function insertBooksToCart(){
			$data = array(
						'isbn' 			=> $this->input->post('isbn'),
						'basketid' 		=> $this->session->userdata('basketid'),
						'number' 		=> $this->input->post('quantity'),
						'warehousecode' => $this->input->post('warehousecode')
					);	 
			$insertToCart = $this->db->insert('contains', $data);
			
			$update = array(
							'isbn' 			=> $this->input->post('isbn'),
							'warehousecode' => $this->input->post('warehousecode'),
							'number' 		=> $this->input->post('numBooks') - $this->input->post('quantity')
						);
			$this->db->where('isbn',$this->input->post('isbn'));
			$this->db->where('warehousecode',$this->input->post('warehousecode'));
			$updateStocks = $this->db->update('stocks', $update);
			
			return $insertToCart;
		}

		public function getCartCount(){
			$this->db->select('sum(number) as bookCount');
			$this->db->from('contains');
			$this->db->where('basketid',$this->session->userdata('basketid')); 

			return $this->db->get()->row()->bookCount;
			/*if($query->num_rows() > 0){
				return $query->result();
			}*/
		}
	}
?>