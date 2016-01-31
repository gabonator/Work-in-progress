<?php
class SynoDLMHostUlozto
{
        private $Url;
        private $Username;
        private $Password;
        private $HostInfo;

        public function __construct($Url, $Username, $Password, $HostInfo) {
                $this->Url = $Url;
                $this->Username = $Username;
                $this->Password = $Password;
                $this->HostInfo = $HostInfo;
        }

        public function GetDownloadInfo() {
                $ret = FALSE;
                $VerifyRet = $this->Verify(FALSE);
                if ($VerifyRet) {
                    $DownloadInfo = array();
                    $DownloadInfo[DOWNLOAD_URL] = $this->GetDownloadLink($this->Url);
                    $ret=$DownloadInfo;
                }
                return  $ret;
        }

        public function Verify($ClearCookie)
        {
                return USER_IS_FREE;
        }

        private function GetDownloadLink($url) 
        {
                $ret = FALSE;

                $queryUrl = "http://localhost:8034/?getDownload('".urlencode($url)."')";

                $curl = curl_init();
//                curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
//                curl_setopt($curl, CURLOPT_USERAGENT, DOWNLOAD_STATION_USER_AGENT);
//                curl_setopt($curl, CURLOPT_POST, TRUE);
//                curl_setopt($curl, CURLOPT_HEADER, TRUE);
                curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
                curl_setopt($curl, CURLOPT_URL, $queryUrl);

                $newUrl = curl_exec($curl);

                curl_close($curl);

                return $newUrl;
        }
}
?>