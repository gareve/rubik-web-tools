<?hh
require $_SERVER['DOCUMENT_ROOT'] . '/config_speedcubing_memo.hh';

echo <img src="../controllers/rubik_gen.hh" />;

$username = 'gareve';
$password = 'mongopw1';

$mongo = new MongoClient('mongodb://ds033419.mongolab.com:33419',[]);
$db = $mongo->selectDB("heroku_app28342778");
$db->authenticate($username,$password);
$states = $db->selectCollection('rubik_states');

$cursor = $states->find();
$cursor->batchSize(2);
$cursor->limit(4);

$cursor->next();
$current = $cursor->current();
krumo($current['name']);