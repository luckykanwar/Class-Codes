<?php
	//echo '<div class="col-lg-0"></div>';
			echo '<div class ="col-lg-12">';	               
			echo '<div class="div-table" style="font-weight:bold">
			 			<div class="div-row">
			   				<div class="div-table-col">Title</div>
			   				<div class="div-table-col">ISBN</div>
			   				<div class="div-table-col">In Stock</div>
			   				<div class="div-table-col">Location</div>
			   				<div class="div-table-col">Cost of book</div>
			   				<div class="div-table-col">Enter Quantity</div>
			   				<div class="div-table-col">Add to Cart</div>
			   			</div>
				  </div>';
	foreach($result as $result){
		echo '
		        <form action = "addtocart" method="post">
			        <div class="div-table">
			            <div class="div-row">
			                <div class="div-table-col"><span><input type="hidden" name="title" value="'.$result->title.'">'.$result->title.'</input></span></div>
			                <div class="div-table-col"><span><input type="hidden" name="isbn" value="'.$result->isbn.'">'.$result->isbn.'</input></span></div>
			                <div class="div-table-col"><span><input type="hidden" name="numBooks" value="'.$result->number.'">'.$result->number.'</input></span></div>
			                <div class="div-table-col"><span><input type="hidden" name="warehouse" value="'.$result->name.'">'.$result->name.'</input></span></div>
			                <div class="div-table-col"><span><input type="hidden" name="price" value="'.$result->price.'">'.$result->price.'</input></span></div>
			                <input type="text" value="'.$result->warehousecode.'" id="warehousecode" name="warehousecode" style="display:none"/>
			                <div class="div-table-col"><span><input type="text" value="" placeholder="Enter quantity" id="quantity" name="quantity" /></div>
			                <div class="div-table-col"><button type="submit" value="Add to Cart">Add to Cart</button></div>
			            </div>
			        </div>		
			    </form>			                		        		
			 ';
	}
	echo '</div>';
?>