<?php
require_once 'RomaClient.php';

/**
 * Test class for RomaClient.
 * Generated by PHPUnit on 2010-08-05 at 16:37:31.
 */
class RomaClientJointTest2 extends PHPUnit_Framework_TestCase
{

  //protected $roma_client;
  protected $server_script_path = '../../roma_root/roma.bash';

  /**
   * Sets up the fixture, for example, opens a network connection.
   * This method is called before a test is executed.
   *
   * @access protected
   */
  protected function setUp(){
    //$this->roma_client = RomaClient::getInstance(array("localhost_11211","localhost_11212"));
  }

  /**
   * Tears down the fixture, for example, closes a network connection.
   * This method is called after a test is executed.
   *
   * @access protected
   */
  protected function tearDown(){
    //exec($this->server_script_path . ' stops');
  }

  /**
   * No.3
   * No.
   */
  public function testNode2Stop() {
    print "\n***TEST*** ". get_class($this) ."::". __FUNCTION__ . "\n";
    exec($this->server_script_path . ' starts');
    sleep(15);
    exec($this->server_script_path . ' stop2');
    sleep(20);
    $roma_client = RomaClient::getInstance(array("localhost_11211", "localhost_11212"));
    $roma_client->set("test-node2-stop", "test-node2-stop", 1000);
    $val = $roma_client->get("test-node2-stop");
    exec($this->server_script_path . ' stops');
    $this->assertEquals("test-node2-stop", $val);
  }
}
?>
