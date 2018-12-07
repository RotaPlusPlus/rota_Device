import sys
import subprocess

# OSC送信のため
import argparse
from pythonosc import osc_message_builder
from pythonosc import udp_client

def get_lines(cmd):
    '''
    :param cmd: str 実行するコマンド.
    :rtype: generator
    :return: 標準出力 (行毎).
    '''
    proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    while True:
        line = proc.stdout.readline()
        if line:
            yield line

        if not line and proc.poll() is not None:
            break

# OSCのSender初期化
def init_osc_sender(sender_ip,sender_port):
    parser = argparse.ArgumentParser()
    parser.add_argument("--sender_ip", default=sender_ip, help="The ip of th OSC Sender")
    parser.add_argument("--sender_port", type=int, default=sender_port, help="The port the OSC sender is listening on")
    args = parser.parse_args()
    osc_client = udp_client.UDPClient(args.sender_ip, args.sender_port)

    # 設定のログ出し
    print("[Sender] sender_ip:{}, sender_port:{}, address:/data".format(args.sender_ip, args.sender_port))
    return osc_client

# OSCでメッセージの送信
def send(osc_client, iter, humidity, temperature):
  msg = osc_message_builder.OscMessageBuilder(address="/data")

  # 更新時間を送信
  update_time = str(time.asctime().split(" ")[3])
  msg.add_arg(update_time)
  print("update_time: {}".format(update_time))

  # OSCのbody
  msg.add_arg(iter)
  msg.add_arg(humidity)
  msg.add_arg(temperature)

  msg = msg.build()
  osc_client.send(msg)


if __name__ == '__main__':

    # ipアドレス
    sender_ip = ""

    # port
    sender_port=""

    # OSC周りの初期化
    osc_client_sender = init_osc_sender(sender_ip,sender_port)

    # RN-42の接続コマンド
    comand = ""

    for line in get_lines(cmd=comand):

        term = line.split(',')

        iter = term[0]
        humidity = term[2]
        temperature = term[3]
        send(osc_client, iter, humidity, temperature)

        # 標準出力
        sys.stdout.buffer.write(line)

# 11,200,60,25
# 12,200,60,25
# 13,200,60,25
# 14,200,60,25
# 15,200,60,25
# 16,200,60,25
