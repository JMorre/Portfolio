<?php

header("Access-Control-Allow-Origin: *");

//Post new recipes new(account_id, name, public, json array of ingredients)
//Post Update recipe update(recipe_id, account_id, json recipe data)
//Delete Recipe delete(recipe_id, account_id)
//Get specific recipe (and ingredients) get_one(recipe_id, account_id)
//Get recipes available to account get_all(account_id)
include_once __DIR__ . '/' . 'DbConnection.php';

$conn = new DbConnection();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $json = file_get_contents('php://input');
    $data = json_decode($json, true);
    switch ($data['type']) {
        case 'new':
            if(!empty($data['accountID']) && !empty($data['name']) && !empty($data['ingredients'])){
                $recipe_query = <<<SQL
INSERT INTO recipe (account_id, name, public) VALUES(?,?,?);
SQL;
                $stmt = $conn->prepare($recipe_query);
                $stmt->execute([$data['accountID'], $data['name'], false]);
                $ingredients = $data['ingredients'];
                $recipe_id_query = <<<SQL
SELECT id from recipe WHERE account_id = ? and name = ? ORDER BY id DESC LIMIT 1;
SQL;
                $stmt = $conn->prepare($recipe_id_query);
                $stmt->execute([$data['accountID'], $data['name']]);
                $recipe_id = $stmt->fetchColumn();
                $ingredient_query = <<<SQL
INSERT INTO ingredient (name) VALUE (?);
SQL;
                $ingredient_names = [];
                $conn->beingTransaction();
                $stmt = $conn->prepare($ingredient_query);
                foreach($ingredients as $ingredient){
                    $stmt->execute([$ingredient['name']]);
                    array_push($ingredient_names, $ingredient['name']);
                }
                $conn->commit();
                $place_holders = implode(',', array_fill(0, count($ingredient_names), '?'));
                $ingredient_query = "SELECT id, name from ingredient WHERE name in ($place_holders);";
                $stmt = $conn->prepare($ingredient_query);
                $stmt->execute($ingredient_names);
                $returned = $stmt->fetchAll(PDO::FETCH_ASSOC);
                $nameToID = [];
                foreach( $returned as $key=>$value){
                    $nameToID[$value['name']] = $value['id'];
                }
                $ingredient_query = <<<SQL
INSERT INTO recipe_ingredient (recipe_id, ingredient_id, amount, unit) VALUES (?, ?, ?, ?);
SQL;

                $conn->beingTransaction();
                $stmt = $conn->prepare($ingredient_query);
                foreach ($ingredients as $ingredient) {
                    $ingredient_id = $nameToID[$ingredient['name']];
                    $stmt->execute([$recipe_id, $ingredient_id, floatval($ingredient['amount']), $ingredient['unit']]);
                }
                $conn->commit();
                echo json_encode(['recipeID'=>$recipe_id]);
            }
            else{
                echo json_encode('');
            }
            break;
        case 'update':
            if (!empty($data['recipe_id']) && !empty($data['accountID'])) {
                $query = <<<SQL
SELECT * FROM recipe where id = ? AND account_id = ?;
SQL;
                $stmt = $conn->prepare($query, [$data['recipe_id'], $data['accountID']]);
                if($stmt->rowCount() == 1){
                    $new_recipe = json_decode($data['recipe']);
                    if(!empty($new_recipe['name']) && !empty($new_recipe['public'])){
                        $query = <<<SQL
UPDATE recipe SET name = ?, public = ? WHERE id = ?;
SQL;
                        $stmt = $conn->prepare($query);
                        $stmt->execute([$new_recipe['name'], $new_recipe['public']]);
                        echo 0;
                    }
                    else{
                        echo json_encode('');
                    }
                }
                else{
                    echo json_encode('');
                }

            } else {
                echo json_encode('');
            }
            break;
        case 'delete':
            if (!empty($data['ID']) && !empty($data['accountID'])) {
                $query = <<<SQL
SELECT * FROM recipe where id = ? AND (account_id = ? or public = TRUE);
SQL;
                $stmt = $conn->prepare($query);
                $stmt->execute([$data['ID'], $data['accountID']]);
                if($stmt->rowCount() == 1){
                    $recipeID = $stmt->fetchColumn();
                    $query = <<<SQL
DELETE FROM recipe WHERE id = ?;
SQL;
                    $stmt = $conn->prepare($query);
                    $stmt->execute([$recipeID]);
                    echo json_encode(['status' => 'success']);
                }
                else{
                    echo json_encode(['more than one recipe found', $stmt->rowCount()]);
                }
            } else {
                echo json_encode('missing name or accountID');
            }
            break;
        default:
            echo json_encode('');
    }
}
elseif ($_SERVER['REQUEST_METHOD'] === 'GET'){
    switch ($_GET['type']){
        case 'one':
            if(!empty($_GET['recipeID']) && !empty($_GET['accountID'])){
                $query = <<<SQL
SELECT id as recipeID, account_id as accountID, name, public from recipe where id = ? and (account_id = ? or public = TRUE);
SQL;

                $stmt = $conn->prepare($query);
                $stmt->execute([$_GET['recipeID'], $_GET['accountID']]);
                $recipe = $stmt->fetchAll(PDO::FETCH_ASSOC)[0];
                $recipe_query = <<<SQL
SELECT i.name as name, recipe_ingredient.id as ingredientID, amount, unit FROM recipe_ingredient
    left join ingredient i on recipe_ingredient.ingredient_id = i.id
    WHERE recipe_id = ?;
SQL;

                $stmt = $conn->prepare($recipe_query);
                $stmt->execute([$_GET['recipeID']]);
                $ingredients = $stmt->fetchAll(PDO::FETCH_ASSOC);
                $recipe['ingredients'] = $ingredients;
                $json = json_encode($recipe);
                echo $json;
            }
            else{
                echo json_encode('');
            }
            break;
        case 'all':
            if(!empty($_GET['accountID'])){
                $query = <<<SQL
SELECT id as recipeID, name, public, account_id as accountID from recipe where account_id = ? or public = TRUE;
SQL;
                $stmt = $conn->prepare($query);
                $stmt->execute([$_GET['accountID']]);
                $recipes = $stmt->fetchAll(PDO::FETCH_ASSOC);
                $json = json_encode(['recipes'=>$recipes]);
                echo $json;
            }
            else{
                echo json_encode('no accountID');
            }
            break;
    }
}

else {
    echo json_encode('');
}
