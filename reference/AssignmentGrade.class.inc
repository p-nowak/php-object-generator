<?php
/*
 * mysql> describe assignment_grade;
 * +---------------+------------------+------+-----+---------+-------+
 * | Field         | Type             | Null | Key | Default | Extra |
 * +---------------+------------------+------+-----+---------+-------+
 * | assignment_id | int(10) unsigned | NO   | PRI | 0       |       |
 * | student_id    | int(10) unsigned | NO   | PRI | 0       |       |
 * | points        | int(10) unsigned | YES  |     | NULL    |       |
 * | grade_id      | int(10) unsigned | YES  |     | NULL    |       |
 * | comment       | varchar(255)     | YES  |     | NULL    |       |
 * | is_waived     | tinyint(4)       | NO   |     | NULL    |       |
 * | due           | date             | YES  |     | NULL    |       |
 * | assigned      | date             | YES  |     | NULL    |       |
 * +---------------+------------------+------+-----+---------+-------+
 */

/**
 * <b>AssignmentGrade</b> class with integrated CRUD methods.
 * @author Php Object Generator
 * @version POG 3.2 / PHP5.1 MYSQL
 * @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
 * @copyright All business logic is copyright WINGS 2013. POG framework is free for personal & commercial use. (Offered under the BSD license)
 * @link http://www.phpobjectgenerator.com/?language=php5&wrapper=pog&objectName=AssignmentGrade&attributeList=array+%28%0A++0+%3D%3E+%27assignment_id%27%2C%0A++1+%3D%3E+%27student_id%27%2C%0A++2+%3D%3E+%27points%27%2C%0A++3+%3D%3E+%27grade_id%27%2C%0A++4+%3D%3E+%27comment%27%2C%0A++5+%3D%3E+%27is_waived%27%2C%0A++6+%3D%3E+%27due%27%2C%0A++7+%3D%3E+%27assigned%27%2C%0A%29&typeList=array+%28%0A++0+%3D%3E+%27INT%27%2C%0A++1+%3D%3E+%27INT%27%2C%0A++2+%3D%3E+%27INT%27%2C%0A++3+%3D%3E+%27INT%27%2C%0A++4+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++5+%3D%3E+%27TINYINT%27%2C%0A++6+%3D%3E+%27DATE%27%2C%0A++7+%3D%3E+%27DATE%27%2C%0A%29
 * @link http://www.phpobjectgenerator.com/?
 */

require_once('WPOGBase.class.inc');
class AssignmentGrade extends WPOGBase
{

	/**
	 * @var int
	 */
	private $assignment_id = '';
	
	/**
	 * @var int
	 */
	private $student_id;
	
	/**
	 * @var int
	 */
	private $points;
 		
	/**
	 * @var year
	 */
	private $grade_id;
	
	/**
	 * @var varchar(255)
	 */
	private $comment;
	
	/**
	 * @var tinyint(4)
	 */
	private $is_waived;
	
	/**
	 * @var date
	 */
	private $due;
	
	/**
	 * @var date
	 */
	private $assigned;

	private $pog_attribute_type = array(
		"assignment_id" => array('db_attributes' => array("NUMERIC", "INT", "10")),
		"student_id" => array('db_attributes' => array("NUMERIC", "INT", "10")),
		"points" => array('db_attributes' => array("NUMERIC", "INT", "10")),
		"grade_id" => array('db_attributes' => array("NUMERIC", "INT", "10")),
		"comment" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"is_waived" => array('db_attributes' => array("NUMERIC", "TINYINT", "4")),
		"due" => array('db_attributes' => array("NUMERIC", "DATE")),
		"assigned" => array('db_attributes' => array("NUMERIC", "DATE")),
		);
		
	/**
	 * A class variable
	 */
	public $pog_query;
	
	protected $connection;
	
	/**
	* Getter for some private attributes
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
	
	function AssignmentGrade($assignment_id='', $student_id='', $points='', $grade_id='', $comment='', $is_waived='', $due='', $assigned='')
	{
		global $DATABASEPDO;
		$this->connection = $DATABASEPDO;
		$this->assignment_id = $assignment_id;
		$this->student_id = $student_id;
		$this->points = $points;
		$this->grade_id = $grade_id;
		$this->comment = $comment;
		$this->is_waived = $is_waived;
		$this->due = $due;
		$this->assigned = $assigned;
	}
	
	
	/**
	* Gets object from database
	* @param integer $assignment_id 
	* @param integer $student_id 
	* @return object $AssignmentGrade
	*/
	function get($assignment_id = null, $student_id = null)
	{
		$assignment_id = (int) $assignment_id;
		if ( $assignment_id == 0 ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Invalid ID: $assignment_id.");
		}
		
		$student_id = (int) $student_id;
		if ( $student_id == 0 ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Invalid ID: $student_id.");
		}
		
		// Throw an error if not found
		$this->pog_query = "select * from `assignment_grade` where `assignment_id`='".intval($assignment_id)."' AND `student_id`='".intval($student_id)."' LIMIT 1";
		if ( $cursor = Database::Reader($this->pog_query, $this->connection) ) {
			if ($cursor->fetchColumn() == 0 ) {
				throw new Exception( __FILE__ ." : ".  __LINE__ ." : Assignment Grade with Assignment ID $assignment_id and Student ID $student_id not found.");
			}
		} else {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Query ". $this->pog_query ." failed" );
		}
		
		if ( $cursor = Database::Reader($this->pog_query, $this->connection) ) {
			while ($row = Database::Read($cursor)) {
				$this->assignment_id = $this->Unescape($row['assignment_id']);
				$this->student_id = $this->Unescape($row['student_id']);
				$this->points = $this->Unescape($row['points']);
				$this->grade_id = $this->Unescape($row['grade_id']);
				$this->comment = $this->Unescape($row['comment']);
				$this->is_waived = $this->Unescape($row['is_waived']);
				$this->due = $row['due'];
				$this->assigned = $row['assigned'];
			}
		} else {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Query ". $this->pog_query ."  failed. Is the table is empty?");
		}
	}
	
	/**
	* Moved. Use ApprovalCollection class instaead.
	*/
	//function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	//{
	//}
	
	
	/**
	* Saves the object to the database
	* Notes: To prevent dups, you should first check for existing record. Record = existing row with given a student id and year.
	* @return bool true if successful, false if not
	*/
	function save()
	{
		
		$rows = 0;
		if ($this->assignment_id!='' && $this->assignment_id!='') {
			$this->pog_query = "select assignment_id, student_id from `assignment_grade` where `assignment_id`='".intval($assignment_id)."' AND `student_id `='".intval($student_id)."' LIMIT 1";
			$rows = Database::Query($this->pog_query, $this->connection);
		}
		if ($rows > 0) {
			$this->pog_query = "update `assignment_grade` set 
			`assignment_id`='".$this->Escape($this->assignment_id)."', 
			`student_id`='".$this->Escape($this->student_id)."', 
			`points`='".$this->Escape($this->points)."', 
			`grade_id`='".$this->Escape($this->grade_id)."', 
			`comment`='".$this->Escape($this->comment)."', 
			`is_waived`='".$this->Escape($this->is_waived)."', 
			`due`='".$this->due."', 
			`assigned`='".$this->assigned."' where `assignment_id`='".$this->assignment_id."' AND  `student_id`='".$this->student_id."'" ;
		} else {
			$this->pog_query = "insert into `assignment_grade` (`assignment_id`, `student_id`, `points`, `grade_id`, `comment`, `is_waived`, `due`, `assigned` ) values (
			'".$this->Escape($this->assignment_id)."', 
			'".$this->Escape($this->student_id)."', 
			'".$this->Escape($this->points)."', 
			'".$this->Escape($this->grade_id)."', 
			'".$this->Escape($this->comment)."', 
			'".$this->Escape($this->is_waived)."', 
			'".$this->due."', 
			'".$this->assigned."' )";
		}
		
		Database::InsertOrUpdate($this->pog_query, $this->connection);
		return true;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @param integer $assignment_id 
	* @param integer $student_id 
	* @return bool true if successful, false if not
	*/
	function saveNew($assignment_id, $student_id)
	{
		$assignment_id = (int) $assignment_id;
		if ( $assignment_id == 0 ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Invalid ID: $assignment_id.");
		}
		
		$student_id = (int) $student_id;
		if ( $student_id == 0 ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Invalid ID: $student_id.");
		}
		
		$this->assignment_id = $assignment_id;
		$this->student_id = $student_id;
		return $this->Save();
	}
	
	
	/**
	 */
}
?>
