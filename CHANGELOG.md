# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-11-02
### Added
- Библиотека матриц на C (C11, row-major).
- Базовый API:
  - `mat_create / mat_free`
  - `mat_get / mat_set / mat_fill`
  - `mat_add / mat_sub / mat_transpose`
- Демка: `matrixlab_demo`.
- Тесты: `test_matrix`, `test_ops` (через CTest).
- GitHub Actions (Ubuntu): сборка и прогон тестов на каждый push/PR.
- Защита от ошибок: безопасный доступ к данным (проверки `NULL` и границ).

### Fixed
- Падение на Linux CI из-за зависимости от `libm` в тестах — убрано.

### Notes
- Хранение данных: построчно (row-major), индекс: `data[i*cols + j]`.
- Совместимость: Windows / Linux (CI).
