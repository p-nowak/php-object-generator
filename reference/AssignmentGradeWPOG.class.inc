<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `slp_approval` (
	`id` int(11) NOT NULL auto_increment,
	`id` INT NOT NULL,
	`student_id` INT NOT NULL,
	`approver_id` INT NOT NULL,
	`year` SMALLINT NOT NULL,
	`approved` DATETIME NOT NULL, PRIMARY KEY  (`idid`)) ENGINE=Innodb;
*/

/**
 * <b>slp_approval</b> class with integrated CRUD methods.
 * @author Php Object Generator
 * @version POG 3.3 / PHP5.1 MYSQL
 * @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
 * @copyright Free for personal & commercial use. (Offered under the BSD license)
 * @link https://wingsdev.local/wings/pog/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=slp_approval&attributeList=array+%28%0A++0+%3D%3E+%27id%27%2C%0A++1+%3D%3E+%27student_id%27%2C%0A++2+%3D%3E+%27approver_id%27%2C%0A++3+%3D%3E+%27year%27%2C%0A++4+%3D%3E+%27approved%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527DATETIME%2527%252C%250A%2529&classList=array+%28%0A++0+%3D%3E+%27%27%2C%0A++1+%3D%3E+%27%27%2C%0A++2+%3D%3E+%27%27%2C%0A++3+%3D%3E+%27%27%2C%0A++4+%3D%3E+%27%27%2C%0A%29
 */
require_once('WPOGBase.class.inc');
class slp_approval extends WPOGBase
{
	/**
	 * @var INT
	 */
	protected $id;
	
	/**
	 * @var INT
	 */
	protected $student_id;
	
	/**
	 * @var INT
	 */
	protected $approver_id;
	
	/**
	 * @var SMALLINT
	 */
	protected $year;
	
	/**
	 * @var DATETIME
	 */
	protected $approved;
	
	public $pog_attribute_type = array(
		"id" => array('db_attributes' => array("NUMERIC", "INT")),
		"student_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"approver_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"year" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"approved" => array('db_attributes' => array("TEXT", "DATETIME")),
		);
	
	
	public $pog_query;
	
	protected $connection;
	
	
	
	/**
	 * Magic getter for some private attributes
	 * @return mixed $attribute
	 */
	public function __get($attribute)
	{
		if (isset($this->{"_".$attribute})) {
			return $this->{"_".$attribute};
		} else {
			return false;
		}
	}
	
	function slp_approval($id='', $student_id='', $approver_id='', $year='', $approved='')
	{
		global $DATABASEPDO;
		$this->connection = $DATABASEPDO;
		$this->id = $id;
		$this->student_id = $student_id;
		$this->approver_id = $approver_id;
		$this->year = $year;
		$this->approved = $approved;
	}
	
	
	/**
	 * Gets object from database
	 * @param integer $id 
	 * @return object $slp_approval
	 */
	function get($id= null)
	{
		$id = (int) $id;
		if ($id == 0) {
		throw new Exception( __FILE__ ." : ".  __LINE__ ." : ID is null or 0: $this->attributeList[0].");
		}

		$this->pog_query = "select * from `slp_approval` where `id` = '".intval($id)."' LIMIT 1";
		if ( 0 == Database::Query($this->pog_query, $this->connection) ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Query ". $this->pog_query ."  failed. Is the table is empty?");
		}
		
		$cursor = Database::Reader($this->pog_query, $this->connection);
		while ($row = Database::Read($cursor)) {
			$this->id = $this->Unescape($row['id']);
			$this->student_id = $this->Unescape($row['student_id']);
			$this->approver_id = $this->Unescape($row['approver_id']);
			$this->year = $this->Unescape($row['year']);
			$this->approved = $row['approved'];
		}
		return $this;
	}
	
	
	/**
	 * Moved. Use collection object class instead.
	 * @return null
	 */
	//function getList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	//{
	//}
	
	
	/**
	 * Saves the object to the database
	 * @return integer $id
	 */
	function save($deep = true)
	{
		$rows = 0;
		if ($this->id!=''){
			$this->pog_query = "select `id` from `slp_approval` where `id` = '".$this->id."' LIMIT 1";
			$rows = Database::Query($this->pog_query, $connection);
		}
		if ($rows > 0) {
			$this->pog_query = "update `slp_approval` set 
				`id`='".$this->Escape($this->id)."', 
				`student_id`='".$this->Escape($this->student_id)."', 
				`approver_id`='".$this->Escape($this->approver_id)."', 
				`year`='".$this->Escape($this->year)."', 
				`approved`='".$this->approved."' where `id`='".$this->id."'";
		} else {
			$this->pog_query = "insert into `slp_approval` (`student_id`, `approver_id`, `year`, `approved` ) values (
			'".$this->Escape($this->student_id)."', 
			'".$this->Escape($this->approver_id)."', 
			'".$this->Escape($this->year)."', 
			'".$this->approved."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->id == "") {
			$this->id = $insertId;
		}
		return $this->get_id();
	}
	
	
	/**
	 * Clones the object and saves it to the database
	 * @return integer $id
	 */
	function saveNew($deep = false)
	{
		$this->id = '';
		return $this->save();
	}
	
	
	/**
	 * Deletes the object from the database
	 * @return boolean
	 */
	function delete($deep = false, $across = false)
	{
		$this->pog_query = "delete from `slp_approval` where `id` = '".$this->id."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	 * Moved. Use collection object class instead.
	 * @return null
	 */
	//function deleteList($fcv_array)
	//{
	//}
	
	
	/**
	 * Get property
	 * @return int $id
	 */
	function get_id()
	{
		return $this->id;
	}
	
	
	/**
	 * Get property
	 * @return int $student_id
	 */
	function get_student_id()
	{
		return $this->student_id;
	}
	
	
	/**
	 * Get property
	 * @return int $approver_id
	 */
	function get_approver_id()
	{
		return $this->approver_id;
	}
	
	
	/**
	 * Get property
	 * @return smallint $year
	 */
	function get_year()
	{
		return $this->year;
	}
	
	
	/**
	 * Get property
	 * @return datetime $approved
	 */
	function get_approved()
	{
		return $this->approved;
	}
	
	
	/**
	 * Set property 
	 * @param int $id 
	 * @return bool true on success. false on error.
	 */
	function set_id($id = null)
	{
		$this->id = $id;
		return true;
	}
	
	
	/**
	 * Set property 
	 * @param int $student_id 
	 * @return bool true on success. false on error.
	 */
	function set_student_id($student_id = null)
	{
		$this->student_id = $student_id;
		return true;
	}
	
	
	/**
	 * Set property 
	 * @param int $approver_id 
	 * @return bool true on success. false on error.
	 */
	function set_approver_id($approver_id = null)
	{
		$this->approver_id = $approver_id;
		return true;
	}
	
	
	/**
	 * Set property 
	 * @param smallint $year 
	 * @return bool true on success. false on error.
	 */
	function set_year($year = null)
	{
		$this->year = $year;
		return true;
	}
	
	
	/**
	 * Set property 
	 * @param datetime $approved 
	 * @return bool true on success. false on error.
	 */
	function set_approved($approved = null)
	{
		$this->approved = $approved;
		return true;
	}
}
?>