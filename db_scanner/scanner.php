<?php

global $message;

?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>POG DB table scanner</title>
    <link rel="stylesheet"
          href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.5/css/bootstrap.css"/>
    <link rel="stylesheet"
          href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.5/css/bootstrap-theme.css"/>
</head>
<body>
<div class="container">
    <?php if($message): ?>
        <div class="alert alert-danger" role="alert">
            <span class="glyphicon glyphicon-exclamation-sign" aria-hidden="true"></span>
            <span class="sr-only">Error:</span>
            <?=$message; ?>
        </div>
    <?php endif; ?>

    <form method="POST" action="process.php">
        <div class="form-group">
            <label>DB Host</label>
            <input type="text" class="form-control" name="host" value="<?=(isset($_POST['host'])?$_POST['host']:'localhost'); ?>" required>
        </div>
        <div class="form-group">
            <label>DB Username</label>
            <input type="text" class="form-control" name="username" value="<?=(isset($_POST['username'])?$_POST['username']:''); ?>" required>
        </div>
        <div class="form-group">
            <label>DB Password</label>
            <input type="password" class="form-control" name="password" value="<?=(isset($_POST['password'])?$_POST['password']:''); ?>" required>
        </div>
        <div class="form-group">
            <label>DB Name</label>
            <input type="text" class="form-control" name="db_name" value="<?=(isset($_POST['db_name'])?$_POST['db_name']:''); ?>" required>
        </div>
        <div class="form-group">
            <label>Table Name</label>
            <input type="text" class="form-control" name="table_name" value="<?=(isset($_POST['db_name'])?$_POST['db_name']:''); ?>" required>
        </div>
        <div class="form-group">
            <label>Object Name</label>
            <input type="text" class="form-control" name="object_name" value="<?=(isset($_POST['object_name'])?$_POST['object_name']:''); ?>" required>
        </div>
        <input type="hidden" name="send" value="1" />
        <button type="submit" class="btn btn-default">Process</button>
    </form>
</div>
</body>
</html>