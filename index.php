<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="css/style.css" rel="stylesheet">
    <title>Текущее время сервера</title>
</head>
<body>
    <div id="time">Загрузка...</div>
    
    <script>
        function updateTime() {
            fetch('server.php')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('time').textContent = data.time;
                })
                .catch(error => console.error('Ошибка:', error));
        }

        setInterval(updateTime, 1000);

        updateTime();
    </script>
</body>
</html>