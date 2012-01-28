<?php
/**
 * AntiSpam.inc
 *
 * This file contains the Framework_Form_AntiSpam class.
 *
 * PHP versions 4 and 5
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Form
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    SVN: 1
 */
/**
 * This class extends the Framework_Form class and implements some
 * methods that facilitate the verification of spam. It uses three
 * methods to verify this: the honeypot, spinner and the timestamp.
 *
 * All of these elements are verified against pre-established
 * standards.
 *
 * @tutorial http://nedbatchelder.com/text/stopbots.html
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Form
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 * @abstract
 */
abstract class Framework_Form_AntiSpam extends Framework_Form
{
    private $_honeypot;
    private $_spinner;
    private $_timestamp;

    private static $_TIMESTAMP_INTERVAL = 1800; // 30min

    /**
     * Constructs the AntiSpam fields in the form.
     *
     * @param array $params the parameters
     */
    public function __construct($params = array())
    {
        if (sizeof($params) > 0
            && isset($_SESSION['anti_spam'])
        ) {
            if (isset($params[$_SESSION['anti_spam']['honeypot']])) {
                $this->_honeypot = $params[$_SESSION['anti_spam']['honeypot']];
            } else {
                $this->_honeypot = null;
            }
            $this->_spinner = isset($params['spinner']) ? $params['spinner'] : null;
            if (isset($params['timestamp'])) {
                $this->_timestamp = $params['timestamp'];
            }
        } else {
            $this->regenerateAntiSpam();
        }
        parent::__construct($params);
    }
    /**
     * Regenerates the elements of the AntiSpam verification.
     *
     * @return void
     */
    public function regenerateAntiSpam()
    {
        $this->_timestamp = time();
        $this->_spinner = sha1(
            $_SERVER['REMOTE_ADDR'] . $this->_timestamp . session_id() . 'spinner'
        );
        $this->_honeypot = '';
        if (true === isset($_SESSION['anti_spam'])) {
            unset($_SESSION['anti_spam']);
        }
        $_SESSION['anti_spam'] = array(
            'honeypot'  => substr(
                str_pad(dechex(mt_rand()), 8, '0', STR_PAD_LEFT), -8
            ),
            'timestamp' => $this->_timestamp,
            'spinner'   => $this->_spinner
        );
    }
    /**
     * Validates the antispam fields.
     *
     * @access public
     * @return bool
     */
    public function validateAntiSpam()
    {
        $return_val = true;
        if ($this->_honeypot === null
            || ($this->_honeypot !== null
            && $this->_honeypot !== '')
        ) {
            write_error_msg(
                get_called_class(),
                'honeypot has been tampered with:' . $this->_honeypot . ';'
            );
            $return_val =  false;
        }

        if ($this->_timestamp === null
            || $this->_timestamp > $_SESSION['anti_spam']['timestamp']
            || time() - $this->_timestamp > self::$_TIMESTAMP_INTERVAL
        ) {
            write_error_msg(
                get_called_class(),
                'TimeStamp has expired or not valid:' + $this->_timestamp
            );
            $return_val = false;
        }

        $old_spinner = $_SESSION['anti_spam']['spinner'];
        if ($this->_spinner === null
            || $old_spinner !== $this->_spinner
        ) {
            write_error_msg(
                get_called_class(),
                'Received Spinner is not the same as the server\'s'
            );
            $return_val = false;
        }

        if (false === $return_val) {
            $this->a_err_messages['generic']
                = gettext(
                    'Ocorreu um erro ao submeter o seu formulario.'
                );
        }

        return $return_val;
    }
    /**
     * Validates the form.
     *
     * @see Framework_Form::validate()
     *
     * @return boolean
     */
    public function validate()
    {
        return $this->validateAntiSpam() && parent::validate();
    }
    /**
     * Returns the honeypot value.
     *
     * @return string
     */
    public function getHoneypot()
    {
        return $_SESSION['anti_spam']['honeypot'];
    }
    /**
     * Returns the spinner value.
     *
     * @return string
     */
    public function getSpinner()
    {
        return $this->_spinner;
    }
    /**
     * Returns the timestamp value.
     *
     * @return string
     */
    public function getTimestamp()
    {
        return $this->_timestamp;
    }
}