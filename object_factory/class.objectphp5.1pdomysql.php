<?php
class Object
{
	var $string;
	var $sql;
	var $objectName;
	var $attributeList;
	var $typeList;
	var $separator = "\n\t";
	var $pdoDriver = "";
	var $language = 'php5.1';
	var $classList;


	// -------------------------------------------------------------
	function Object($objectName, $attributeList = '', $typeList ='', $pdoDriver = '', $language = 'php5.1', $classList)
	{
		$this->objectName = $objectName;
		$this->attributeList = $attributeList;
		$this->typeList = $typeList;
		$this->pdoDriver = $pdoDriver;
		$this->language = $language;
		$this->classList = $classList;
	}

	// -------------------------------------------------------------
	function BeginObject()
	{
		$impArray = array();
		$misc = new Misc(array());
		$this->string = "<?php\n";
		$this->string .= $this->CreatePreface();
		$this->string .= "\nrequire_once('WPOGBase.class.inc');";
		foreach ($this->typeList as $key => $type)
		{
			if ($type == "JOIN")
			{
				$this->string .= "\ninclude_once('class.".strtolower($misc->MappingName($this->objectName, $this->attributeList[$key])).".php');";
			}
			if ($type == "BELONGSTO" || $type == "HASMANY")
			{
				if(in_array(strtolower($this->classList[$key]), $impArray) == false)
					$this->string .= "\ninclude_once('class.".strtolower($this->classList[$key]).".php');";

				array_push($impArray, strtolower($this->classList[$key])) ;
			}
		}
		$this->string .= "\nclass ".$this->objectName." extends WPOGBase\n{\n\t";
		$this->string.="private \$".strtolower($this->objectName)."Id = '';\n\n\t";
		$x = 0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$x] == "BELONGSTO")
			{
				$this->string .="/**\n\t";
				$this->string .=" * @var INT(11)\n\t";
				$this->string .=" */\n\t";
				$this->string.="public $".strtolower($attribute)."Id;\n\t";
				$this->string.="\n\t";
			}
			else if ($this->typeList[$x] == "HASMANY" || $this->typeList[$x] == "JOIN")
			{
				$this->string .="/**\n\t";
				$this->string .=" * @var private array of $attribute objects\n\t";
				$this->string .=" */\n\t";
				$this->string.="private \$_".strtolower($attribute)."List = array();\n\t";
				$this->string.="\n\t";
			}
			else
			{
				$this->string .="/**\n\t";
				$this->string .=" * @var ".stripcslashes($this->typeList[$x])."\n\t";
				$this->string .=" */\n\t";
				$this->string.="protected $".$attribute.";\n\t";
				$this->string.="\n\t";
			}
			$x++;
		}
		
		//	create attribute => type array map
		//	needed for setup
		$this->string .= "public \$pog_attribute_type = array(\n\t\t";
		$x = 0;
		foreach ($this->attributeList as $attribute)
		{
			$this->string .= "\"".$attribute."\" => array('db_attributes' => array(\"".$misc->InterpretType($this->typeList[$x])."\", \"".$misc->getAttributeType($this->typeList[$x])."\"".(($misc->InterpretLength($this->typeList[$x]) != null) ?  ', "'.$misc->InterpretLength($this->typeList[$x]).'"' : '').")),\n\t\t";
			$x++;
		}
		$this->string .= ");\n\t";
		$this->string .= "public \$pog_query;";
		$this->string .= "\n\tprotected \$connection;";
	}

	// -------------------------------------------------------------
	function EndObject()
	{
		$this->string .= "\n}\n?>";
	}

	// -------------------------------------------------------------
	function CreateConstructor()
	{
		$this->string .= "\n\t\n\tfunction ".$this->objectName."(";
		$i = 0;
		$j = 0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$i] != "BELONGSTO" && $this->typeList[$i] != "HASMANY" && $this->typeList[$i] != "JOIN")
			{
				if ($j == 0)
				{
					$this->string .= '$'.$attribute.'=\'\'';
				}
				else
				{
					$this->string .= ', $'.$attribute.'=\'\'';
				}
				$j++;
			}
			$i++;
		}
		$this->string .= ")\n\t{";
		$this->string .= "\n\t\tglobal \$DATABASEPDO;";
		$this->string .= "\n\t\t\$this->connection = \$DATABASEPDO;";
		$x = 0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$x] == "HASMANY" || $this->typeList[$x] == "JOIN")
			{
				$this->string .="\n\t\t\$this->_".strtolower($attribute)."List = array();";
			}
			else if ($this->typeList[$x] != "BELONGSTO")
			{
				$this->string .= "\n\t\t\$this->".$attribute." = $".$attribute.";";
			}
			$x++;
		}
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	function CreateSQLQuery()
	{
		$this->sql .= "\tCREATE TABLE `".strtolower($this->objectName)."` (\n\t`".strtolower($this->attributeList[0])."` int(11) NOT NULL auto_increment,";
		$x=0;
		$indexesToBuild = array();
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$x] == "BELONGSTO")
			{
				$indexesToBuild[] = "`".strtolower($attribute)."id`";
				$this->sql .= "\n\t`".strtolower($attribute)."id` int(11) NOT NULL,";
			}
			else if ($this->typeList[$x] != "HASMANY" && $this->typeList[$x] != "JOIN")
			{
				$this->sql .= "\n\t`".strtolower($attribute)."` ".stripcslashes($this->typeList[$x])." NOT NULL,";
			}
			$x++;
		}
		if (sizeof($indexesToBuild) > 0)
		{
			$this->sql .= " INDEX(".implode(',', $indexesToBuild)."),";
		}
		$this->sql .= " PRIMARY KEY  (`".strtolower($this->objectName)."id`)) ENGINE=Innodb;";
	}

	// -------------------------------------------------------------
	function CreateComments($description='', $parameterDescriptionArray='', $returnType='')
	{
		$this->string .= "/**\n"
		."\t * $description\n";
		if ($parameterDescriptionArray != '')
		{
			foreach ($parameterDescriptionArray as $parameter)
			{
				$this->string .= "\t * @param $parameter \n";
			}
		}
		 $this->string .= "\t * @return $returnType\n"
		 ."\t */\n";
	}

	// -------------------------------------------------------------
	function CreatePreface()
	{
		$this->string .= "/*\n\tThis SQL query will create the table to store your object.\n";
		$this->CreateSQLQuery();
		$this->string .= "\n".$this->sql."\n*/";
		$this->string .= "\n\n/**";
		$this->string .= "\n * <b>".$this->objectName."</b> class with integrated CRUD methods.";
		$this->string .= "\n * @author ".$GLOBALS['configuration']['author'];
		$this->string .= "\n * @version POG ".$GLOBALS['configuration']['versionNumber'].$GLOBALS['configuration']['revisionNumber']." / ".strtoupper($this->language)." MYSQL";
		$this->string .= "\n * @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql";
		$this->string .= "\n * @copyright ".$GLOBALS['configuration']['copyright'];
		$this->string .= "\n * @link ".$GLOBALS['configuration']['urlGenerator']."/?language=".$this->language."&wrapper=pdo&pdoDriver=".$this->pdoDriver."&objectName=".urlencode($this->objectName)."&attributeList=".urlencode(var_export($this->attributeList, true))."&typeList=".urlencode(urlencode(var_export($this->typeList, true)))."&classList=".urlencode(var_export($this->classList, true));
		$this->string .= "\n */";
	}


	// Essential functions
	// -------------------------------------------------------------
	function CreateMagicGetterFunction()
	{
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Getter for some private attributes",'',"mixed \$attribute");
		$this->string .= "\tpublic function __get(\$attribute)\n\t{";
		$this->string .= "\n\t\tif (isset(\$this->{\"_\".\$attribute})) {";
		$this->string .= "\n\t\t\treturn \$this->{\"_\".\$attribute};";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\treturn false;";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t}";
	}
	
	// -------------------------------------------------------------
	function CreateSaveFunction($deep = false)
	{
		$misc = new Misc(array());
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Saves the object to the database",'',"integer $".strtolower($this->objectName)."Id");
		if ($deep)
		{
			$this->string .= "\tfunction save(\$deep = true)\n\t{";
		}
		else
		{
			$this->string .= "\tfunction save()\n\t{";
		}
		
		$this->string .= "\n\t\t\$rows = 0;";
		$this->string .= "\n\t\tif (\$this->".strtolower($this->attributeList[0])."!=''){";
		$this->string .= "\n\t\t\t\$this->pog_query = \"select `".strtolower($this->attributeList[0])."` from `".strtolower($this->objectName)."` where `".strtolower($this->objectName)."id`='\".\$this->".strtolower($this->attributeList[0]).".\"' LIMIT 1\";";
		$this->string .= "\n\t\t\t\$rows = Database::Query(\$this->pog_query, \$connection);";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\tif (\$rows > 0) {";
		$this->string .= "\n\t\t\t\$this->pog_query = \"update `".strtolower($this->objectName)."` set ";
		$x=1;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$x] != "HASMANY" && $this->typeList[$x] != "JOIN")
			{
				if ($x == (count($this->attributeList)-1))
				{
					// don't encode enum values.
					// we could also check the attribute type at runtime using the attribute=>array map
					// but this solution is more efficient
					if (strtolower(substr($this->typeList[$x],0,4)) == "enum" || strtolower(substr($this->typeList[$x],0,3)) == "set" || strtolower(substr($this->typeList[$x],0,4)) == "date" || strtolower(substr($this->typeList[$x],0,4)) == "time" || $this->typeList[$x] == "BELONGSTO")
					{
						if ($this->typeList[$x] == "BELONGSTO")
						{
							$this->string .= "\n\t\t\t\t`".strtolower($attribute)."id`='\".\$this->".strtolower($this->attributeList[0]).".\"' ";
						}
						else
						{
							$this->string .= "\n\t\t\t\t`".strtolower($attribute)."`='\".\$this->$attribute.\"' ";
						}
					}
					else
					{
						$this->string .= "\n\t\t\t\t`".strtolower($attribute)."`='\".\$this->Escape(\$this->$attribute).\"' ";
					}
				}
				else
				{
					if (strtolower(substr($this->typeList[$x],0,4)) == "enum" || strtolower(substr($this->typeList[$x],0,3)) == "set" || strtolower(substr($this->typeList[$x],0,4)) == "date" || strtolower(substr($this->typeList[$x],0,4)) == "time" || $this->typeList[$x] == "BELONGSTO")
					{
						if ($this->typeList[$x] == "BELONGSTO")
						{
							$this->string .= "\n\t\t\t\t`".strtolower($attribute)."ID`='\".\$this->".strtolower($attribute).".\"', ";
						}
						else
						{
							$this->string .= "\n\t\t\t\t`".strtolower($attribute)."`='\".\$this->$attribute.\"', ";
						}
					}
					else
					{
						$this->string .= "\n\t\t\t\t`".strtolower($attribute)."`='\".\$this->Escape(\$this->$attribute).\"', ";
					}
				}
			}
			$x++;
		}
		if (substr($this->string, strlen($this->string) - 2) == ", ")
		{
			$this->string = substr($this->string, 0, strlen($this->string) - 2);
		}
		$this->string .= "where `".strtolower($this->attributeList[0])."`='\".\$this->".strtolower($this->attributeList[0]).".\"'\";";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\$this->pog_query = \"insert into `".strtolower($this->objectName)."` (";
		$y=0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$y] != "HASMANY"  && $this->typeList[$y] != "JOIN")
			{
				if ($y == (count($this->attributeList)-1))
				{
					if ($this->typeList[$y] == "BELONGSTO")
					{
						$this->string .= "`".strtolower($attribute)."ID` ";
					}
					else
					{
						$this->string .= "`".strtolower($attribute)."` ";
					}
				}
				else
				{
					if ($this->typeList[$y] == "BELONGSTO")
					{
						$this->string .= "`".strtolower($attribute)."ID`, ";
					}
					else
					{
						$this->string .= "`".strtolower($attribute)."`, ";
					}
				}
			}
			$y++;
		}
		if (substr($this->string, strlen($this->string) - 2) == ", ")
		{
			$this->string = substr($this->string, 0, strlen($this->string) - 2);
		}
		$this->string .= ") values (";
		$z=0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$z] != "HASMANY" && $this->typeList[$z] != "JOIN")
			{
				if ($z == (count($this->attributeList)-1))
				{
					if (strtolower(substr($this->typeList[$z],0,4)) == "enum" || strtolower(substr($this->typeList[$z],0,3)) == "set"  || strtolower(substr($this->typeList[$z],0,4)) == "date" || strtolower(substr($this->typeList[$z],0,4)) == "time" || $this->typeList[$z] == "BELONGSTO")
					{
						if ($this->typeList[$z] == "BELONGSTO")
						{
							$this->string .= "\n\t\t\t'\".\$this->".strtolower($attribute).".\"' ";
						}
						else
						{
							$this->string .= "\n\t\t\t'\".\$this->$attribute.\"' ";
						}
					}
					else
					{
						$this->string .= "\n\t\t\t'\".\$this->Escape(\$this->$attribute).\"' ";
					}
				}
				else
				{
					if (strtolower(substr($this->typeList[$z],0,4)) == "enum" || strtolower(substr($this->typeList[$z],0,3)) == "set"  || strtolower(substr($this->typeList[$z],0,4)) == "date" || strtolower(substr($this->typeList[$z],0,4)) == "time" || $this->typeList[$z] == "BELONGSTO")
					{
						if ($this->typeList[$z] == "BELONGSTO")
						{
							$this->string .= "\n\t\t\t'\".\$this->".strtolower($attribute).".\"', ";
						}
						else
						{
							$this->string .= "\n\t\t\t'\".\$this->$attribute.\"', ";
						}
					}
					else
					{
						$this->string .= "\n\t\t\t'\".\$this->Escape(\$this->$attribute).\"', ";
					}
				}
			}
			$z++;
		}
		if (substr($this->string, strlen($this->string) - 2) == ", ")
		{
			$this->string = substr($this->string, 0, strlen($this->string) - 2);
		}
		$this->string .= ")\";";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\t\$insertId = Database::InsertOrUpdate(\$this->pog_query, \$connection);";
		$this->string .= "\n\t\tif (\$this->".strtolower($this->attributeList[0])." == \"\") {";
		$this->string .= "\n\t\t\t\$this->".strtolower($this->attributeList[0])." = \$insertId;";
		$this->string .= "\n\t\t}";
		if ($deep)
		{
			$this->string .= "\n\t\tif (\$deep) {";
			$i = 0;
			foreach ($this->typeList as $type)
			{
				if ($type == "HASMANY")
				{
					$this->string .= "\n\t\t\tforeach (\$this->_".strtolower($this->attributeList[$i])."List as $".strtolower($this->attributeList[$i]).") {";
					$this->string .= "\n\t\t\t\t\$".strtolower($this->attributeList[$i])."->".strtolower($this->objectName)."Id = \$this->".strtolower($this->objectName)."Id;";
					$this->string .= "\n\t\t\t\t\$".strtolower($this->attributeList[$i])."->save(\$deep);";
					$this->string .= "\n\t\t\t}";
				}
				else if ($type == "JOIN")
				{
					$this->string .= "\n\t\t\tforeach (\$this->_".strtolower($this->attributeList[$i])."List as $".strtolower($this->attributeList[$i]).") {";
					$this->string .= "\n\t\t\t\t\$".strtolower($this->attributeList[$i])."->save();";
					$this->string .= "\n\t\t\t\t\$map = new ".$misc->MappingName($this->objectName, $this->attributeList[$i])."();";
					$this->string .= "\n\t\t\t\t\$map->addMapping(\$this, \$".strtolower($this->attributeList[$i]).");";
					$this->string .= "\n\t\t\t}";
				}

				$i++;
			}
			$this->string .= "\n\t\t}";
		}
		$this->string .= "\n\t\treturn \$this->".strtolower($this->attributeList[0]).";";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	function CreateSaveNewFunction($deep = false)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Clones the object and saves it to the database",'',"integer $".strtolower($this->attributeList[0]));
		if ($deep)
		{
			$this->string .="\tfunction saveNew(\$deep = false)\n\t{";
		}
		else
		{
			$this->string .="\tfunction saveNew()\n\t{";
		}
		$this->string .= "\n\t\t\$this->".strtolower($this->attributeList[0])." = '';";
		if ($deep)
		{
			$this->string .= "\n\t\treturn \$this->save(\$deep);";
		}
		else
		{
			$this->string .= "\n\t\treturn \$this->save();";
		}
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	function CreateDeleteFunction($deep = false)
	{
		$misc = new Misc(array());
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Deletes the object from the database",'',"boolean");
		if ($deep)
		{
			$this->string .= "\tfunction delete(\$deep = false, \$across = false)\n\t{";
		}
		else
		{
			$this->string .= "\tfunction delete()\n\t{";
		}
		if ($deep)
		{
			if (in_array("HASMANY", $this->typeList))
			{
				$this->string .= "\n\t\tif (\$deep) {";
				$i = 0;
				foreach ($this->typeList as $type)
				{
					if ($type == "HASMANY")
					{
						$this->string .= "\n\t\t\t$".strtolower($this->attributeList[$i])."List = \$this->get".ucfirst(strtolower($this->attributeList[$i]))."List();";
						$this->string .= "\n\t\t\tforeach ($".strtolower($this->attributeList[$i])."List as $".strtolower($this->attributeList[$i]).") {";
						$this->string .= "\n\t\t\t\t\$".strtolower($this->attributeList[$i])."->delete(\$deep, \$across);";
						$this->string .= "\n\t\t\t}";
					}
					$i++;
				}
				$this->string .= "\n\t\t}";
			}
			if (in_array("JOIN", $this->typeList))
			{
				$this->string .= "\n\t\tif (\$across) {";
				$i = 0;
				foreach ($this->typeList as $type)
				{
					if ($type == "JOIN")
					{
						$this->string .= "\n\t\t\t$".strtolower($this->attributeList[$i])."List = \$this->get".ucfirst(strtolower($this->attributeList[$i]))."List();";
						$this->string .= "\n\t\t\t\$map = new ".$misc->MappingName($this->objectName, $this->attributeList[$i])."();";
						$this->string .= "\n\t\t\t\$map->RemoveMapping(\$this);";
						$this->string .= "\n\t\t\tforeach (\$".strtolower($this->attributeList[$i])."List as \$".strtolower($this->attributeList[$i]).") {";
						$this->string .= "\n\t\t\t\t\$".strtolower($this->attributeList[$i])."->delete(\$deep, \$across);";
						$this->string .= "\n\t\t\t}";
					}
					$i++;
				}
				$this->string .= "\n\t\t} else {";
				$j = 0;
				foreach ($this->typeList as $type)
				{
					if ($type == "JOIN")
					{
						$this->string .= "\n\t\t\t\$map = new ".$misc->MappingName($this->objectName, $this->attributeList[$j])."();";
						$this->string .= "\n\t\t\t\$map->RemoveMapping(\$this);";
					}
					$j++;
				}
				$this->string .= "\n\t\t}";
			}
		}
		$this->string .= "\n\t\t\$this->pog_query = \"delete from `".strtolower($this->objectName)."` where `".strtolower($this->objectName)."id`='\".\$this->".strtolower($this->attributeList[0]).".\"'\";";
		$this->string .= "\n\t\treturn Database::NonQuery(\$this->pog_query, \$connection);";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	function CreateDeleteListFunction($deep = false)
	{
		// Moved. Use object collection class instead.
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Moved. Use collection object class instead.",'',"null");
		$this->string .= "\t//function deleteList(\$fcv_array)\n\t//{";
		$this->string .= "\n\t//}";
	}

	// -------------------------------------------------------------
	function CreateGetFunction()
	{
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Gets object from database",array("integer \$".strtolower($this->attributeList[0])),"object \$".$this->objectName);
		$this->string .="\tfunction get(\$".strtolower($this->attributeList[0]).")\n\t{";
		$this->string .= "\n\t\t\$this->pog_query = \"select * from `".strtolower($this->objectName)."` where `".strtolower($this->attributeList[0])."`='\".intval(\$".strtolower($this->attributeList[0]).").\"' LIMIT 1\";";
		
		$this->string .= "\n\t\t\$this->attributeList[0] = (int) \$this->attributeList[0];";
		$this->string .= "\n\t\tif ( \$this->attributeList[0] == 0 ) {";
		$this->string .= "\n\t\tthrow new Exception( __FILE__ .\" : \".  __LINE__ .\" : Invalid ID: \$this->attributeList[0].\");";
		$this->string .= "\n\t\t}";
		$this->string .= "\n";
		
		$this->string .= "\n\t\tif ( 0 == Database::Query(\$this->pog_query, \$this->connection) ) {";
		$this->string .= "\n\t\t\tthrow new Exception( __FILE__ .\" : \".  __LINE__ .\" : Query \". \$this->pog_query .\"  failed. Is the table is empty?\");";
		$this->string .= "\n\t\t}";
		$this->string .= "\n";
		$this->string .= "\n\t\t\$cursor = Database::Reader(\$this->pog_query, \$connection);";
		$this->string .= "\n\t\twhile (\$row = Database::Read(\$cursor)) {";
		$x = 0;
		foreach ($this->attributeList as $attribute)
		{
			if ($this->typeList[$x] != "HASMANY" && $this->typeList[$x] != "JOIN")
			{
				if (strtolower(substr($this->typeList[$x],0,4)) == "enum" || strtolower(substr($this->typeList[$x],0,3)) == "set" || strtolower(substr($this->typeList[$x],0,4)) == "date" || strtolower(substr($this->typeList[$x],0,4)) == "time" || $this->typeList[$x] == "BELONGSTO")
				{
					if ($this->typeList[$x] == "BELONGSTO")
					{
						$this->string .= "\n\t\t\t\$this->".strtolower($this->attributeList[0])." = \$row['".strtolower($this->attributeList[0])."'];";
					}
					else
					{
						$this->string .= "\n\t\t\t\$this->".$attribute." = \$row['".strtolower($attribute)."'];";
					}
				}
				else
				{
					$this->string .= "\n\t\t\t\$this->".$attribute." = \$this->Unescape(\$row['".strtolower($attribute)."']);";
				}
			}
			$x++;
		}
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\treturn \$this;";
		$this->string .= "\n\t}";
	}
	
	// -------------------------------------------------------------
	function CreateGetFunctions()
	{
		foreach ($this->attributeList as $attribute)
		{
			$this->string .= "\n\t".$this->separator."\n\t";
			$this->string .= $this->CreateComments("Get property",array("integer \$".strtolower($this->attributeList[0])),"object \$".$this->objectName);
			$this->string .="\tfunction get_".$attribute."(\$".strtolower($this->attributeList[0]).")\n\t{";
			//$this->string .= "\n\t\twhile (\$row = Database::Read(\$cursor)) {";
			$x = 0;
			$x++;
			$this->string .= "\n\t\treturn \$this->".$attribute.";";
			$this->string .= "\n\t}";
		}
	}
	
	// -------------------------------------------------------------
	function CreateSetFunctions()
	{
		$x = 0;
		foreach ($this->attributeList as $attribute)
		{
			$this->string .= "\n\t".$this->separator."\n\t";
			$this->string .= $this->CreateComments("Set property", array($typeList[$x] . " \$". $attribute), "bool true on success. false on error.");
			$this->string .="\tfunction set_".$attribute. "(\$". $attribute . " = null)\n\t{";
			$this->string .= "\n\t\t\$this->".$attribute." = \$". $attribute ;
			$this->string .= "\n\t\treturn true;";
			$this->string .= "\n\t}";
			$x++;
		}
	}
	
	// -------------------------------------------------------------
	function CreateGetListFunction()
	{
		// Moved. Use object collection class instead.
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Moved. Use collection object class instead.",'',"null");
		$this->string .= "\t//function getList(\$fcv_array = array(), \$sortBy='', \$ascending=true, \$limit='')\n\t//{";
		$this->string .= "\n\t//}";
	}


	// Relations {1-1, 1-Many, Many-1} functions
	// -------------------------------------------------------------
	function CreateAddChildFunction($child)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Associates the $child object to this one",'',"");
		$this->string .= "\tfunction add".ucfirst(strtolower($child))."(&\$".strtolower($child).")\n\t{";
		$this->string .= "\n\t\t\$".strtolower($child)."->".strtolower($this->attributeList[0])." = \$this->".strtolower($this->attributeList[0]).";";
		$this->string .= "\n\t\t\$found = false;";
		$this->string .= "\n\t\tforeach(\$this->_".strtolower($child)."List as \$".strtolower($child)."2) {";
		$this->string .= "\n\t\t\tif (\$".strtolower($child)."->".strtolower($child)."Id > 0 && \$".strtolower($child)."->".strtolower($child)."Id == \$".strtolower($child)."2->".strtolower($child)."Id) {";
		$this->string .= "\n\t\t\t\t\$found = true;";
		$this->string .= "\n\t\t\t\tbreak;";
		$this->string .= "\n\t\t\t}";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\tif (!\$found) {";
		$this->string .= "\n\t\t\t\$this->_".strtolower($child)."List[] = \$".strtolower($child).";";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateGetChildrenFunction($child, $class)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Gets a list of $child objects associated to this one", array("multidimensional array {(\"field\", \"comparator\", \"value\"), (\"field\", \"comparator\", \"value\"), ...}","string \$sortBy","boolean \$ascending","int limit"),"array of $child objects");
		$this->string .= "\tfunction get".ucfirst(strtolower($child))."List(\$fcv_array = array(), \$sortBy='', \$ascending=true, \$limit='')\n\t{";
		$this->string .= "\n\t\t\$".strtolower($child)." = new ".$class."();";
		$this->string .= "\n\t\t\$fcv_array[] = array(\"".strtolower($this->attributeList[0])."\", \"=\", \$this->".strtolower($this->attributeList[0]).");";
		$this->string .= "\n\t\t\$dbObjects = \$".strtolower($child)."->getList(\$fcv_array, \$sortBy, \$ascending, \$limit);";
		$this->string .= "\n\t\treturn \$dbObjects;";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateSetChildrenFunction($child)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Makes this the parent of all $child objects in the $child List array. Any existing $child will become orphan(s)",'',"null");
		$this->string .= "\tfunction set".ucfirst(strtolower($child))."List(&\$list)\n\t{";
		$this->string .= "\n\t\t\$this->_".strtolower($child)."List = array();";
		$this->string .= "\n\t\t\$existing".ucfirst(strtolower($child))."List = \$this->get".ucfirst(strtolower($child))."List();";
		$this->string .= "\n\t\tforeach (\$existing".ucfirst(strtolower($child))."List as \$".strtolower($child).") {";
		$this->string .= "\n\t\t\t\$".strtolower($child)."->".strtolower($this->attributeList[0])." = '';";
		$this->string .= "\n\t\t\t\$".strtolower($child)."->save(false);";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\t\$this->_".strtolower($child)."List = \$list;";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateSetParentFunction($parent)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Associates the $parent object to this one",'',"");
		$this->string .= "\tfunction set".ucfirst(strtolower($parent))."(&\$".strtolower($parent).")\n\t{";
		$this->string .= "\n\t\t\$this->".strtolower($parent)."Id = $".strtolower($parent)."->".strtolower($parent)."Id;";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateGetParentFunction($parent, $class)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Associates the $parent object to this one",'',"boolean");
		$this->string .= "\tfunction get".ucfirst(strtolower($parent))."()\n\t{";
		$this->string .= "\n\t\t\$".strtolower($parent)." = new ".$class."();";
		$this->string .= "\n\t\treturn $".strtolower($parent)."->get(\$this->".strtolower($parent)."Id);";
		$this->string .= "\n\t}";
	}


	// Relations {Many-Many} functions

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateAddAssociationFunction($sibling)
	{
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Associates the $sibling object to this one",'',"");
		$this->string .= "\tfunction add".ucfirst(strtolower($sibling))."(&\$".strtolower($sibling).")\n\t{";
		$this->string .= "\n\t\tif (\$".strtolower($sibling)." instanceof ".$sibling.") {";
		$this->string .= "\n\t\t\tif (in_array(\$this, \$".strtolower($sibling)."->".strtolower($this->objectName)."List, true)) {";
		$this->string .= "\n\t\t\t\treturn false;";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\$found = false;";
		$this->string .= "\n\t\t\t\tforeach (\$this->_".strtolower($sibling)."List as \$".strtolower($sibling)."2) {";
		$this->string .= "\n\t\t\t\t\tif (\$".strtolower($sibling)."->".strtolower($sibling)."Id > 0 && \$".strtolower($sibling)."->".strtolower($sibling)."Id == \$".strtolower($sibling)."2->".strtolower($sibling)."Id) {";
		$this->string .= "\n\t\t\t\t\t\t\$found = true;";
		$this->string .= "\n\t\t\t\t\t\tbreak;";
		$this->string .= "\n\t\t\t\t\t}";
		$this->string .= "\n\t\t\t\t}";
		$this->string .= "\n\t\t\t\tif (!\$found) {";
		$this->string .= "\n\t\t\t\t\t\$this->_".strtolower($sibling)."List[] = \$".strtolower($sibling).";";
		$this->string .= "\n\t\t\t\t}";
		$this->string .= "\n\t\t\t}";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t}";
	}

	//-------------------------------------------------------------
	// @todo: Implement and test
	function CreateGetAssociationsFunction($sibling)
	{
		$misc = new Misc(array());
		$this->string .= "\n\t".$this->separator."\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Returns a sorted array of objects that match given conditions",array("multidimensional array {(\"field\", \"comparator\", \"value\"), (\"field\", \"comparator\", \"value\"), ...}","string \$sortBy","boolean \$ascending","int limit"),"array \$".strtolower($this->objectName)."List");
		$this->string .= "\tfunction get".ucfirst(strtolower($sibling))."List(\$fcv_array = array(), \$sortBy='', \$ascending=true, \$limit='')\n\t{";
		$this->string .= "\n\t\t\$sqlLimit = (\$limit != '' ? \"LIMIT \$limit\" : '');";
		$this->string .= "\n\t\t\$".strtolower($sibling)." = new ".$sibling."();";
		$this->string .= "\n\t\t\$".strtolower($sibling)."List = Array();";
		$this->string .= "\n\t\t\$this->pog_query = \"select distinct * from `".strtolower($sibling)."` a INNER JOIN `".strtolower($misc->MappingName($this->objectName, $sibling))."` m ON m.".strtolower($sibling)."id = a.".strtolower($sibling)."id where m.".strtolower($this->objectName)."id = '\$this->".strtolower($this->objectName)."Id' \";";
		$this->string .= "\n\t\tif (sizeof(\$fcv_array) > 0) {";
		$this->string .= "\n\t\t\t\$this->pog_query .= \" AND \";";
		$this->string .= "\n\t\t\tfor (\$i=0, \$c=sizeof(\$fcv_array); \$i<\$c; \$i++) {";
		$this->string .= "\n\t\t\t\tif (sizeof(\$fcv_array[\$i]) == 1) {";
		$this->string .= "\n\t\t\t\t\t\$this->pog_query .= \" \".\$fcv_array[\$i][0].\" \";";
		$this->string .= "\n\t\t\t\t\tcontinue;";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\tif (\$i > 0 && sizeof(\$fcv_array[\$i-1]) != 1) {";
		$this->string .= "\n\t\t\t\t\t\t\$this->pog_query .= \" AND \";";
		$this->string .= "\n\t\t\t\t\t}";
		$this->string .= "\n\t\t\t\t\tif (isset(\$".strtolower($sibling)."->pog_attribute_type[\$fcv_array[\$i][0]]['db_attributes']) && \$".strtolower($sibling)."->pog_attribute_type[\$fcv_array[\$i][0]]['db_attributes'][0] != 'NUMERIC' && \$".strtolower($sibling)."->pog_attribute_type[\$fcv_array[\$i][0]]['db_attributes'][0] != 'SET') {";
		$this->string .= "\n\t\t\t\t\t\tif (\$GLOBALS['configuration']['db_encoding'] == 1) {";
		$this->string .= "\n\t\t\t\t\t\t\t\$value = POG_Base::IsColumn(\$fcv_array[\$i][2]) ? \"BASE64_DECODE(\".\$fcv_array[\$i][2].\")\" : \"'\".\$fcv_array[\$i][2].\"'\";";
		$this->string .= "\n\t\t\t\t\t\t\t\$this->pog_query .= \"BASE64_DECODE(`\".\$fcv_array[\$i][0].\"`) \".\$fcv_array[\$i][1].\" \".\$value;";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\t\t\t\$value =  POG_Base::IsColumn(\$fcv_array[\$i][2]) ? \$fcv_array[\$i][2] : \"'\".\$this->Escape(\$fcv_array[\$i][2]).\"'\";";
		$this->string .= "\n\t\t\t\t\t\t\t\$this->pog_query .= \"a.`\".\$fcv_array[\$i][0].\"` \".\$fcv_array[\$i][1].\" \".\$value;";
		$this->string .= "\n\t\t\t\t\t\t}";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\t\t\$value = POG_Base::IsColumn(\$fcv_array[\$i][2]) ? \$fcv_array[\$i][2] : \"'\".\$fcv_array[\$i][2].\"'\";";
		$this->string .= "\n\t\t\t\t\t\t\$this->pog_query .= \"a.`\".\$fcv_array[\$i][0].\"` \".\$fcv_array[\$i][1].\" \".\$value;";
		$this->string .= "\n\t\t\t\t\t}";
		$this->string .= "\n\t\t\t\t}";
		$this->string .= "\n\t\t\t}";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\tif (\$sortBy != '') {";
		$this->string .= "\n\t\t\tif (isset(\$".strtolower($sibling)."->pog_attribute_type[\$sortBy]['db_attributes']) && \$".strtolower($sibling)."->pog_attribute_type[\$sortBy]['db_attributes'][0] != 'NUMERIC' && \$".strtolower($sibling)."->pog_attribute_type[\$sortBy]['db_attributes'][0] != 'SET') {";
		$this->string .= "\n\t\t\t\tif (\$GLOBALS['configuration']['db_encoding'] == 1) {";
		$this->string .= "\n\t\t\t\t\t\$sortBy = \"BASE64_DECODE(a.\$sortBy) \";";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\t\$sortBy = \"a.\$sortBy \";";
		$this->string .= "\n\t\t\t\t}";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\t\$sortBy = \"a.\$sortBy \";";
		$this->string .= "\n\t\t\t}";
		$this->string .= "\n\t\t} else {";
		$this->string .= "\n\t\t\t\$sortBy = \"a.".strtolower($sibling)."id\";";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\t\$this->pog_query .= \" order by \".\$sortBy.\" \".(\$ascending ? \"asc\" : \"desc\").\" \$sqlLimit\";";
		$this->string .= "\n\t\t\$cursor = Database::Reader(\$this->pog_query, \$connection);";
		$this->string .= "\n\t\twhile(\$rows = Database::Read(\$cursor)) {";
		$this->string .= "\n\t\t\t\$".strtolower($sibling)." = new ".$sibling."();";
		$this->string .= "\n\t\t\tforeach (\$".strtolower($sibling)."->pog_attribute_type as \$attribute_name => \$attrubute_type) {";
		$this->string .= "\n\t\t\t\tif (\$attrubute_type['db_attributes'][1] != \"HASMANY\" && \$attrubute_type['db_attributes'][1] != \"JOIN\") {";
		$this->string .= "\n\t\t\t\t\tif (\$attrubute_type['db_attributes'][1] == \"BELONGSTO\") {";
		$this->string .= "\n\t\t\t\t\t\t\$".strtolower($sibling)."->{strtolower(\$attribute_name).'Id'} = \$rows[strtolower(\$attribute_name).'id'];";
		$this->string .= "\n\t\t\t\t\t\tcontinue;";
		$this->string .= "\n\t\t\t\t\t}";
		$this->string .= "\n\t\t\t\t\t\$".strtolower($sibling)."->{\$attribute_name} = \$this->Escape(\$rows[strtolower(\$attribute_name)]);";
		$this->string .= "\n\t\t\t\t}";
		$this->string .= "\n\t\t\t}";
		$this->string .= "\n\t\t\t\$".strtolower($sibling)."List[] = $".strtolower($sibling).";";
		$this->string .= "\n\t\t}";
		$this->string .= "\n\t\treturn \$".strtolower($sibling)."List;";
		$this->string .= "\n\t}";
	}

	// -------------------------------------------------------------
	// @todo: Implement and test
	function CreateSetAssociationsFunction($sibling)
	{
		$misc = new Misc(array());
		$this->string .= "\n\t$this->separator\n\t";
		$this->string .= $this->CreateComments("Not implemented or tested. Creates mappings between this and all objects in the $sibling List array. Any existing mapping will become orphan(s)",'',"null");
		$this->string .= "\tfunction set".ucfirst(strtolower($sibling))."List(&\$".strtolower($sibling)."List)\n\t{";
		$this->string .= "\n\t\t\$map = new ".$misc->MappingName($this->objectName, $sibling)."();";
		$this->string .= "\n\t\t\$map->RemoveMapping(\$this);";
		$this->string .= "\n\t\t\$this->_".strtolower($sibling)."List = \$".strtolower($sibling)."List;";
		$this->string .= "\n\t}";
	}

}
?>